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
typedef  int /*<<< orphan*/  term_rect_t ;
typedef  int /*<<< orphan*/  term_char_t ;
struct vt_window {int /*<<< orphan*/  vw_buf; } ;
struct terminal {struct vt_window* tm_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  vtbuf_fill (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtterm_fill(struct terminal *tm, const term_rect_t *r, term_char_t c)
{
	struct vt_window *vw = tm->tm_softc;

	vtbuf_fill(&vw->vw_buf, r, c);
}