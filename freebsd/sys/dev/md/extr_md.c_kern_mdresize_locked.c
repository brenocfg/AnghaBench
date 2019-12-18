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
struct md_s {scalar_t__ sectorsize; scalar_t__ mediasize; int flags; } ;
struct md_req {int md_options; scalar_t__ md_mediasize; int /*<<< orphan*/  md_unit; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOENT ; 
 int MD_FORCE ; 
 int MD_RESERVE ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  md_sx ; 
 struct md_s* mdfind (int /*<<< orphan*/ ) ; 
 int mdresize (struct md_s*,struct md_req*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kern_mdresize_locked(struct md_req *mdr)
{
	struct md_s *sc;

	sx_assert(&md_sx, SA_XLOCKED);

	if ((mdr->md_options & ~(MD_FORCE | MD_RESERVE)) != 0)
		return (EINVAL);

	sc = mdfind(mdr->md_unit);
	if (sc == NULL)
		return (ENOENT);
	if (mdr->md_mediasize < sc->sectorsize)
		return (EINVAL);
	if (mdr->md_mediasize < sc->mediasize &&
	    !(sc->flags & MD_FORCE) &&
	    !(mdr->md_options & MD_FORCE))
		return (EBUSY);
	return (mdresize(sc, mdr));
}