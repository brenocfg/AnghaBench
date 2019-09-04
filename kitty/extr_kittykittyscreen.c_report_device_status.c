#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_7__ {int /*<<< orphan*/  mDECOM; } ;
struct TYPE_8__ {unsigned int columns; int /*<<< orphan*/  margin_top; TYPE_2__ modes; int /*<<< orphan*/  lines; TYPE_1__* cursor; } ;
struct TYPE_6__ {unsigned int x; unsigned int y; } ;
typedef  TYPE_3__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  CSI ; 
 unsigned int MAX (unsigned int,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  write_escape_code_to_child (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 

void
report_device_status(Screen *self, unsigned int which, bool private) {
    // We don't implement the private device status codes, since I haven't come
    // across any programs that use them
    unsigned int x, y;
    static char buf[64];
    switch(which) {
        case 5:  // device status
            write_escape_code_to_child(self, CSI, "0n");
            break;
        case 6:  // cursor position
            x = self->cursor->x; y = self->cursor->y;
            if (x >= self->columns) {
                if (y < self->lines - 1) { x = 0; y++; }
                else x--;
            }
            if (self->modes.mDECOM) y -= MAX(y, self->margin_top);
            // 1-based indexing
            int sz = snprintf(buf, sizeof(buf) - 1, "%s%u;%uR", (private ? "?": ""), y + 1, x + 1);
            if (sz > 0) write_escape_code_to_child(self, CSI, buf);
            break;
    }
}