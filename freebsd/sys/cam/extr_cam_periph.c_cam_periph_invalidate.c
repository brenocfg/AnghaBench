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
struct sbuf {int dummy; } ;
struct cam_periph {int flags; int /*<<< orphan*/  (* periph_oninval ) (struct cam_periph*) ;int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_INFO ; 
 int CAM_PERIPH_ANNOUNCED ; 
 int CAM_PERIPH_INVALID ; 
 int CAM_PERIPH_NEW_DEV_FOUND ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 int /*<<< orphan*/  cam_periph_assert (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_release_locked (struct cam_periph*) ; 
 int /*<<< orphan*/  rebooting ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_putbuf (struct sbuf*) ; 
 int /*<<< orphan*/  stub1 (struct cam_periph*) ; 
 int /*<<< orphan*/  xpt_denounce_periph_sbuf (struct cam_periph*,struct sbuf*) ; 

void
cam_periph_invalidate(struct cam_periph *periph)
{

	cam_periph_assert(periph, MA_OWNED);
	/*
	 * We only call this routine the first time a peripheral is
	 * invalidated.
	 */
	if ((periph->flags & CAM_PERIPH_INVALID) != 0)
		return;

	CAM_DEBUG(periph->path, CAM_DEBUG_INFO, ("Periph invalidated\n"));
	if ((periph->flags & CAM_PERIPH_ANNOUNCED) && !rebooting) {
		struct sbuf sb;
		char buffer[160];

		sbuf_new(&sb, buffer, 160, SBUF_FIXEDLEN);
		xpt_denounce_periph_sbuf(periph, &sb);
		sbuf_finish(&sb);
		sbuf_putbuf(&sb);
	}
	periph->flags |= CAM_PERIPH_INVALID;
	periph->flags &= ~CAM_PERIPH_NEW_DEV_FOUND;
	if (periph->periph_oninval != NULL)
		periph->periph_oninval(periph);
	cam_periph_release_locked(periph);
}