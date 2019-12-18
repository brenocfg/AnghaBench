#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ default_orientation; } ;
struct TYPE_7__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_8__ {void* layout; TYPE_1__ rect; } ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,scalar_t__,scalar_t__,void*) ; 
 scalar_t__ HORIZ ; 
 void* L_SPLITH ; 
 void* L_SPLITV ; 
 scalar_t__ NO_ORIENTATION ; 
 TYPE_2__* con_get_output (TYPE_2__*) ; 
 TYPE_3__ config ; 

__attribute__((used)) static void _workspace_apply_default_orientation(Con *ws) {
    /* If default_orientation is set to NO_ORIENTATION we determine
     * orientation depending on output resolution. */
    if (config.default_orientation == NO_ORIENTATION) {
        Con *output = con_get_output(ws);
        ws->layout = (output->rect.height > output->rect.width) ? L_SPLITV : L_SPLITH;
        ws->rect = output->rect;
        DLOG("Auto orientation. Workspace size set to (%d,%d), setting layout to %d.\n",
             output->rect.width, output->rect.height, ws->layout);
    } else {
        ws->layout = (config.default_orientation == HORIZ) ? L_SPLITH : L_SPLITV;
    }
}