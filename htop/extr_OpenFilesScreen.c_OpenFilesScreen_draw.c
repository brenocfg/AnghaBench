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
struct TYPE_8__ {TYPE_1__* process; } ;
struct TYPE_7__ {int /*<<< orphan*/  pid; } ;
struct TYPE_6__ {int /*<<< orphan*/  comm; } ;
typedef  TYPE_2__ OpenFilesScreen ;
typedef  TYPE_3__ InfoScreen ;

/* Variables and functions */
 int /*<<< orphan*/  InfoScreen_drawTitled (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void OpenFilesScreen_draw(InfoScreen* this) {
   InfoScreen_drawTitled(this, "Snapshot of files open in process %d - %s", ((OpenFilesScreen*)this)->pid, this->process->comm);
}