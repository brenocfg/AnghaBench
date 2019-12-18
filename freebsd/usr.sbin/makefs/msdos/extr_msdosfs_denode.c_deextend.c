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
typedef  scalar_t__ u_long ;
struct ucred {int dummy; } ;
struct msdosfsmount {scalar_t__ pm_freeclustercount; } ;
struct denode {int de_Attributes; scalar_t__ de_FileSize; int de_flag; int /*<<< orphan*/ * de_vnode; struct msdosfsmount* de_pmp; } ;

/* Variables and functions */
 int ATTR_DIRECTORY ; 
 int /*<<< orphan*/  DE_CLEAR ; 
 int DE_MODIFIED ; 
 int DE_UPDATE ; 
 int E2BIG ; 
 int EINVAL ; 
 int EISDIR ; 
 int ENOSPC ; 
 int /*<<< orphan*/  FAT32 (struct msdosfsmount*) ; 
 scalar_t__ de_clcount (struct msdosfsmount*,scalar_t__) ; 
 int /*<<< orphan*/  detrunc (struct denode*,scalar_t__,int /*<<< orphan*/ ,struct ucred*) ; 
 int extendfile (struct denode*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
deextend(struct denode *dep, u_long length, struct ucred *cred)
{
	struct msdosfsmount *pmp = dep->de_pmp;
	u_long count;
	int error;

	/*
	 * The root of a DOS filesystem cannot be extended.
	 */
	if (dep->de_vnode != NULL && !FAT32(pmp))
		return (EINVAL);

	/*
	 * Directories cannot be extended.
	 */
	if (dep->de_Attributes & ATTR_DIRECTORY)
		return (EISDIR);

	if (length <= dep->de_FileSize)
		return (E2BIG);

	/*
	 * Compute the number of clusters to allocate.
	 */
	count = de_clcount(pmp, length) - de_clcount(pmp, dep->de_FileSize);
	if (count > 0) {
		if (count > pmp->pm_freeclustercount)
			return (ENOSPC);
		error = extendfile(dep, count, NULL, NULL, DE_CLEAR);
		if (error) {
			/* truncate the added clusters away again */
			(void) detrunc(dep, dep->de_FileSize, 0, cred);
			return (error);
		}
	}

	/*
	 * Zero extend file range; ubc_zerorange() uses ubc_alloc() and a
	 * memset(); we set the write size so ubc won't read in file data that
	 * is zero'd later.
	 */
	dep->de_FileSize = length;
	dep->de_flag |= DE_UPDATE | DE_MODIFIED;
	return 0;
}