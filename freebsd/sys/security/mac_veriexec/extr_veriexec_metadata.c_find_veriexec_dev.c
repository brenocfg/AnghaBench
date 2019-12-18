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
struct veriexec_devhead {int dummy; } ;
struct veriexec_dev_list {scalar_t__ fsid; int /*<<< orphan*/  file_head; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 struct veriexec_dev_list* LIST_FIRST (struct veriexec_devhead*) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct veriexec_devhead*,struct veriexec_dev_list*,int /*<<< orphan*/ ) ; 
 struct veriexec_dev_list* LIST_NEXT (struct veriexec_dev_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_VERIEXEC ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (struct veriexec_dev_list*,int /*<<< orphan*/ ) ; 
 struct veriexec_dev_list* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ve_mutex ; 

__attribute__((used)) static struct veriexec_dev_list *
find_veriexec_dev(dev_t fsid, struct veriexec_devhead *head)
{
	struct veriexec_dev_list *lp;
	struct veriexec_dev_list *np = NULL;

search:
	/* Look for the file system */
	for (lp = LIST_FIRST(head); lp != NULL;
	     lp = LIST_NEXT(lp, entries))
		if (lp->fsid == fsid) break;

	if (lp == NULL) {
		if (np == NULL) {
			/*
			 * If pointer is null then entry not there,
			 * add a new one, first try to malloc while
			 * we hold mutex - should work most of the time.
			 */
			np = malloc(sizeof(struct veriexec_dev_list),
			    M_VERIEXEC, M_NOWAIT);
			if (np == NULL) {
				/*
				 * So much for that plan, dop the mutex
				 * and repeat...
				 */
				mtx_unlock(&ve_mutex);
				np = malloc(sizeof(struct veriexec_dev_list),
				    M_VERIEXEC, M_WAITOK);
				mtx_lock(&ve_mutex);
				/*
				 * Repeat the seach, in case someone
				 * added this while we slept.
				 */
				goto search;
			}
		}
		if (np) {
			/* Add the entry to the list */
			lp = np;
			LIST_INIT(&(lp->file_head));
			lp->fsid = fsid;
			LIST_INSERT_HEAD(head, lp, entries);
		}
	} else if (np) {
		/*
		 * Someone else did it while we slept.
		 */
		mtx_unlock(&ve_mutex);
		free(np, M_VERIEXEC);
		mtx_lock(&ve_mutex);
	}

	return (lp);
}