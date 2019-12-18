#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  size_t uint32_t ;
struct per_user_data {int /*<<< orphan*/  user_data_lock; int /*<<< orphan*/  gref_tree; } ;
struct ioctl_gntdev_alloc_gref {int flags; int count; int /*<<< orphan*/ * gref_ids; void* index; int /*<<< orphan*/  domid; } ;
struct gntdev_gref {int /*<<< orphan*/  gref_id; TYPE_1__* page; int /*<<< orphan*/ * notify; void* file_index; } ;
struct TYPE_8__ {int /*<<< orphan*/  to_kill_grefs_mtx; int /*<<< orphan*/  to_kill_grefs; } ;
struct TYPE_7__ {int /*<<< orphan*/  list; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GNTDEV_ALLOC_FLAG_WRITABLE ; 
 int /*<<< orphan*/  GRANT_REF_INVALID ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  M_GNTDEV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 int PG_ZERO ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gntdev_gref*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct gntdev_gref*,int /*<<< orphan*/ ) ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_NORMAL ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 int /*<<< orphan*/  VM_PAGE_BITS_ALL ; 
 int VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 TYPE_4__ cleanup_data ; 
 int /*<<< orphan*/  cleanup_task ; 
 int devfs_get_cdevpriv (void**) ; 
 int get_file_offset (struct per_user_data*,int,void**) ; 
 int gnttab_grant_foreign_access (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 TYPE_3__ gref_next ; 
 int /*<<< orphan*/  gref_tree_head ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 struct gntdev_gref* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_zero_page (TYPE_1__*) ; 
 int /*<<< orphan*/  suword32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 TYPE_1__* vm_page_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
gntdev_alloc_gref(struct ioctl_gntdev_alloc_gref *arg)
{
	uint32_t i;
	int error, readonly;
	uint64_t file_offset;
	struct gntdev_gref *grefs;
	struct per_user_data *priv_user;

	readonly = !(arg->flags & GNTDEV_ALLOC_FLAG_WRITABLE);

	error = devfs_get_cdevpriv((void**) &priv_user);
	if (error != 0)
		return (EINVAL);

	/* Cleanup grefs and free pages. */
	taskqueue_enqueue(taskqueue_thread, &cleanup_task);

	/* Get file offset for this request. */
	error = get_file_offset(priv_user, arg->count, &file_offset);
	if (error != 0)
		return (error);

	/* Allocate grefs. */
	grefs = malloc(sizeof(*grefs) * arg->count, M_GNTDEV, M_WAITOK);

	for (i = 0; i < arg->count; i++) {
		grefs[i].file_index = file_offset + i * PAGE_SIZE;
		grefs[i].gref_id = GRANT_REF_INVALID;
		grefs[i].notify = NULL;
		grefs[i].page = vm_page_alloc(NULL, 0, VM_ALLOC_NORMAL
			| VM_ALLOC_NOOBJ | VM_ALLOC_WIRED | VM_ALLOC_ZERO);
		if (grefs[i].page == NULL) {
			log(LOG_ERR, "Page allocation failed.");
			error = ENOMEM;
			break;
		}
		if ((grefs[i].page->flags & PG_ZERO) == 0) {
			/*
			 * Zero the allocated page, as we don't want to 
			 * leak our memory to other domains.
			 */
			pmap_zero_page(grefs[i].page);
		}
		grefs[i].page->valid = VM_PAGE_BITS_ALL;

		error = gnttab_grant_foreign_access(arg->domid,
			(VM_PAGE_TO_PHYS(grefs[i].page) >> PAGE_SHIFT),
			readonly, &grefs[i].gref_id);
		if (error != 0) {
			log(LOG_ERR, "Grant Table Hypercall failed.");
			break;
		}
	}

	if (error != 0) {
		/*
		 * If target domain maps the gref (by guessing the gref-id),
		 * then we can't clean it up yet and we have to leave the 
		 * page in place so as to not leak our memory to that domain.
		 * Add it to a global list to be cleaned up later.
		 */
		mtx_lock(&cleanup_data.to_kill_grefs_mtx);
		for (i = 0; i < arg->count; i++)
			STAILQ_INSERT_TAIL(&cleanup_data.to_kill_grefs,
			    &grefs[i], gref_next.list);
		mtx_unlock(&cleanup_data.to_kill_grefs_mtx);
		
		taskqueue_enqueue(taskqueue_thread, &cleanup_task);

		return (error);
	}

	/* Copy the output values. */
	arg->index = file_offset;
	for (i = 0; i < arg->count; i++)
		suword32(&arg->gref_ids[i], grefs[i].gref_id);

	/* Modify the per user private data. */
	mtx_lock(&priv_user->user_data_lock);
	for (i = 0; i < arg->count; i++)
		RB_INSERT(gref_tree_head, &priv_user->gref_tree, &grefs[i]);
	mtx_unlock(&priv_user->user_data_lock);

	return (error);
}