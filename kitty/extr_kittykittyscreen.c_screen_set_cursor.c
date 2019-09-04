#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {TYPE_1__* cursor; } ;
struct TYPE_4__ {int shape; int blink; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */
 int CURSOR_BEAM ; 
 int CURSOR_BLOCK ; 
 int CURSOR_UNDERLINE ; 
 int NO_CURSOR_SHAPE ; 

void
screen_set_cursor(Screen *self, unsigned int mode, uint8_t secondary) {
    uint8_t shape; bool blink;
    switch(secondary) {
        case 0: // DECLL
            break;
        case '"':  // DECCSA
            break;
        case ' ': // DECSCUSR
            shape = 0; blink = false;
            if (mode > 0) {
                blink = mode % 2;
                shape = (mode < 3) ? CURSOR_BLOCK : (mode < 5) ? CURSOR_UNDERLINE : (mode < 7) ? CURSOR_BEAM : NO_CURSOR_SHAPE;
            }
            if (shape != self->cursor->shape || blink != self->cursor->blink) {
                self->cursor->shape = shape; self->cursor->blink = blink;
            }
            break;
    }
}