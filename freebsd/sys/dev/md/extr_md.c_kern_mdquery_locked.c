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
struct md_s {scalar_t__ type; int /*<<< orphan*/  file; int /*<<< orphan*/  label; int /*<<< orphan*/  sectorsize; int /*<<< orphan*/  mediasize; int /*<<< orphan*/  flags; } ;
struct md_req {scalar_t__ md_type; int /*<<< orphan*/ * md_file; int /*<<< orphan*/ * md_label; int /*<<< orphan*/  md_sectorsize; int /*<<< orphan*/  md_mediasize; int /*<<< orphan*/  md_options; int /*<<< orphan*/  md_unit; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ MD_PRELOAD ; 
 scalar_t__ MD_VNODE ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  md_sx ; 
 struct md_s* mdfind (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kern_mdquery_locked(struct md_req *mdr)
{
	struct md_s *sc;
	int error;

	sx_assert(&md_sx, SA_XLOCKED);

	sc = mdfind(mdr->md_unit);
	if (sc == NULL)
		return (ENOENT);
	mdr->md_type = sc->type;
	mdr->md_options = sc->flags;
	mdr->md_mediasize = sc->mediasize;
	mdr->md_sectorsize = sc->sectorsize;
	error = 0;
	if (mdr->md_label != NULL) {
		error = copyout(sc->label, mdr->md_label,
		    strlen(sc->label) + 1);
		if (error != 0)
			return (error);
	}
	if (sc->type == MD_VNODE ||
	    (sc->type == MD_PRELOAD && mdr->md_file != NULL))
		error = copyout(sc->file, mdr->md_file,
		    strlen(sc->file) + 1);
	return (error);
}