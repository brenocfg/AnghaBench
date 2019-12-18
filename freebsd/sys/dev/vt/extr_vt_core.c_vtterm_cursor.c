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
typedef  int /*<<< orphan*/  term_pos_t ;
struct vt_window {int /*<<< orphan*/  vw_buf; } ;
struct terminal {struct vt_window* tm_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  vtbuf_cursor_position (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
vtterm_cursor(struct terminal *tm, const term_pos_t *p)
{
	struct vt_window *vw = tm->tm_softc;

	vtbuf_cursor_position(&vw->vw_buf, p);
}