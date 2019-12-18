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
struct veriexec_dev_list {scalar_t__ fsid; struct veriexec_dev_list* label; struct veriexec_devhead file_head; } ;
struct mac_veriexec_file_info {scalar_t__ fsid; struct mac_veriexec_file_info* label; struct veriexec_devhead file_head; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int ENOENT ; 
 struct veriexec_dev_list* LIST_FIRST (struct veriexec_devhead*) ; 
 struct veriexec_dev_list* LIST_NEXT (struct veriexec_dev_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct veriexec_dev_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_VERIEXEC ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (struct veriexec_dev_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ve_mutex ; 

__attribute__((used)) static int
free_veriexec_dev(dev_t fsid, struct veriexec_devhead *head)
{
	struct veriexec_dev_list *lp;
	struct mac_veriexec_file_info *ip, *nip;

	/* Look for the file system */
	for (lp = LIST_FIRST(head); lp != NULL;
	     lp = LIST_NEXT(lp, entries))
		if (lp->fsid == fsid) break;

	/* If lp is NULL, we did not find it */
	if (lp == NULL)
		return ENOENT;

	/* Unhook lp, before we free it and its content */
	LIST_REMOVE(lp, entries);

	/* Release the lock */
	mtx_unlock(&ve_mutex);

	/* Free the file entries in the list */
	for (ip = LIST_FIRST(&(lp->file_head)); ip != NULL; ip = nip) {
		nip = LIST_NEXT(ip, entries);
		LIST_REMOVE(ip, entries);
		if (ip->label)
			free(ip->label, M_VERIEXEC);
		free(ip, M_VERIEXEC);
	}

	/* Free the meta-data entry for the device */
	free(lp, M_VERIEXEC);

	/* Re-acquire the lock */
	mtx_lock(&ve_mutex);
	return 0;
}