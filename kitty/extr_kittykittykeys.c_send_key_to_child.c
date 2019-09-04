#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* screen; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; TYPE_1__ render_data; } ;
typedef  TYPE_3__ Window ;
struct TYPE_8__ {scalar_t__ mEXTENDED_KEYBOARD; int /*<<< orphan*/  mDECCKM; } ;
struct TYPE_10__ {TYPE_2__ modes; } ;
typedef  TYPE_4__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  APC ; 
 int /*<<< orphan*/  CSI ; 
 char* key_to_bytes (int,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  schedule_write_to_child (int /*<<< orphan*/ ,int,char const*,char const) ; 
 int /*<<< orphan*/  write_escape_code_to_child (TYPE_4__*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline void
send_key_to_child(Window *w, int key, int mods, int action) {
    Screen *screen = w->render_data.screen;
    const char *data = key_to_bytes(key, screen->modes.mDECCKM, screen->modes.mEXTENDED_KEYBOARD, mods, action);
    if (data) {
        if (screen->modes.mEXTENDED_KEYBOARD) {
            if (*data == 1) schedule_write_to_child(w->id, 1, (data + 1), 1);
            else write_escape_code_to_child(screen, APC, data + 1);
        } else {
            if (*data > 2 && data[1] == 0x1b && data[2] == '[') { // CSI code
                write_escape_code_to_child(screen, CSI, data + 3);
            } else schedule_write_to_child(w->id, 1, (data + 1), *data);
        }
    }
}