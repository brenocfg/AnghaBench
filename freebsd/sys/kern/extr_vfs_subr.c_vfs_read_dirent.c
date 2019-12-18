#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct vop_readdir_args {int* a_ncookies; int /*<<< orphan*/ ** a_cookies; TYPE_1__* a_uio; } ;
struct dirent {scalar_t__ d_reclen; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {scalar_t__ uio_resid; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int uiomove (struct dirent*,scalar_t__,TYPE_1__*) ; 

int
vfs_read_dirent(struct vop_readdir_args *ap, struct dirent *dp, off_t off)
{
	int error;

	if (dp->d_reclen > ap->a_uio->uio_resid)
		return (ENAMETOOLONG);
	error = uiomove(dp, dp->d_reclen, ap->a_uio);
	if (error) {
		if (ap->a_ncookies != NULL) {
			if (ap->a_cookies != NULL)
				free(ap->a_cookies, M_TEMP);
			ap->a_cookies = NULL;
			*ap->a_ncookies = 0;
		}
		return (error);
	}
	if (ap->a_ncookies == NULL)
		return (0);

	KASSERT(ap->a_cookies,
	    ("NULL ap->a_cookies value with non-NULL ap->a_ncookies!"));

	*ap->a_cookies = realloc(*ap->a_cookies,
	    (*ap->a_ncookies + 1) * sizeof(u_long), M_TEMP, M_WAITOK | M_ZERO);
	(*ap->a_cookies)[*ap->a_ncookies] = off;
	*ap->a_ncookies += 1;
	return (0);
}