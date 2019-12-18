#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* process; } ;
struct TYPE_5__ {int /*<<< orphan*/  comm; int /*<<< orphan*/  pid; } ;
typedef  TYPE_2__ InfoScreen ;

/* Variables and functions */
 int /*<<< orphan*/  InfoScreen_drawTitled (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void EnvScreen_draw(InfoScreen* this) {
   InfoScreen_drawTitled(this, "Environment of process %d - %s", this->process->pid, this->process->comm);
}