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
struct cursor_attr {int* bg; int mouse_ba; int mouse_ia; int base; int height; int flags; } ;

/* Variables and functions */
 int CONS_CHARCURSOR_COLORS ; 
 int CONS_CURSOR_ATTRS ; 
 int CONS_MOUSECURSOR_COLORS ; 
 int CONS_SHAPEONLY_CURSOR ; 

__attribute__((used)) static void
sc_adjust_ca(struct cursor_attr *cap, int flags, int base, int height)
{
    if (flags & CONS_CHARCURSOR_COLORS) {
	cap->bg[0] = base & 0xff;
	cap->bg[1] = height & 0xff;
    } else if (flags & CONS_MOUSECURSOR_COLORS) {
	cap->mouse_ba = base & 0xff;
	cap->mouse_ia = height & 0xff;
    } else {
	if (base >= 0)
	    cap->base = base;
	if (height >= 0)
	    cap->height = height;
	if (!(flags & CONS_SHAPEONLY_CURSOR))
		cap->flags = flags & CONS_CURSOR_ATTRS;
    }
}