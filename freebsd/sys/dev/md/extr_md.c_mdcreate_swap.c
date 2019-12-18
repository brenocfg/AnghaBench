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
typedef  int vm_ooffset_t ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct md_s {int mediasize; scalar_t__ fwsectors; scalar_t__ fwheads; int flags; int /*<<< orphan*/ * object; } ;
struct md_req {int md_options; int md_mediasize; scalar_t__ md_fwsectors; scalar_t__ md_fwheads; } ;

/* Variables and functions */
 int EDOM ; 
 int EINVAL ; 
 int ENOMEM ; 
 int MD_FORCE ; 
 int MD_RESERVE ; 
 int MD_VERIFY ; 
 int /*<<< orphan*/  OBJT_SWAP ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_PROT_DEFAULT ; 
 int mdsetcred (struct md_s*,int /*<<< orphan*/ ) ; 
 scalar_t__ swap_pager_reserve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_pager_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mdcreate_swap(struct md_s *sc, struct md_req *mdr, struct thread *td)
{
	vm_ooffset_t npage;
	int error;

	/*
	 * Range check.  Disallow negative sizes and sizes not being
	 * multiple of page size.
	 */
	if (sc->mediasize <= 0 || (sc->mediasize % PAGE_SIZE) != 0)
		return (EDOM);

	/*
	 * Allocate an OBJT_SWAP object.
	 *
	 * Note the truncation.
	 */

	if ((mdr->md_options & MD_VERIFY) != 0)
		return (EINVAL);
	npage = mdr->md_mediasize / PAGE_SIZE;
	if (mdr->md_fwsectors != 0)
		sc->fwsectors = mdr->md_fwsectors;
	if (mdr->md_fwheads != 0)
		sc->fwheads = mdr->md_fwheads;
	sc->object = vm_pager_allocate(OBJT_SWAP, NULL, PAGE_SIZE * npage,
	    VM_PROT_DEFAULT, 0, td->td_ucred);
	if (sc->object == NULL)
		return (ENOMEM);
	sc->flags = mdr->md_options & (MD_FORCE | MD_RESERVE);
	if (mdr->md_options & MD_RESERVE) {
		if (swap_pager_reserve(sc->object, 0, npage) < 0) {
			error = EDOM;
			goto finish;
		}
	}
	error = mdsetcred(sc, td->td_ucred);
 finish:
	if (error != 0) {
		vm_object_deallocate(sc->object);
		sc->object = NULL;
	}
	return (error);
}