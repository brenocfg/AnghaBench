#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ttm_object_file {int /*<<< orphan*/ * ref_hash; int /*<<< orphan*/  ref_list; int /*<<< orphan*/  refcount; struct ttm_object_device* tdev; int /*<<< orphan*/  lock; } ;
struct ttm_object_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_TTM_OBJ_FILE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 unsigned int TTM_REF_NUM ; 
 int drm_ht_create (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  drm_ht_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ttm_object_file*,int /*<<< orphan*/ ) ; 
 struct ttm_object_file* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,char*) ; 

struct ttm_object_file *ttm_object_file_init(struct ttm_object_device *tdev,
					     unsigned int hash_order)
{
	struct ttm_object_file *tfile;
	unsigned int i;
	unsigned int j = 0;
	int ret;

	tfile = malloc(sizeof(*tfile), M_TTM_OBJ_FILE, M_WAITOK);
	rw_init(&tfile->lock, "ttmfo");
	tfile->tdev = tdev;
	refcount_init(&tfile->refcount, 1);
	INIT_LIST_HEAD(&tfile->ref_list);

	for (i = 0; i < TTM_REF_NUM; ++i) {
		ret = drm_ht_create(&tfile->ref_hash[i], hash_order);
		if (ret) {
			j = i;
			goto out_err;
		}
	}

	return tfile;
out_err:
	for (i = 0; i < j; ++i)
		drm_ht_remove(&tfile->ref_hash[i]);

	free(tfile, M_TTM_OBJ_FILE);

	return NULL;
}