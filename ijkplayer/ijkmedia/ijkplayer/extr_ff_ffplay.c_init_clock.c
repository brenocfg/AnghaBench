#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double speed; int* queue_serial; scalar_t__ paused; } ;
typedef  TYPE_1__ Clock ;

/* Variables and functions */
 int /*<<< orphan*/  NAN ; 
 int /*<<< orphan*/  set_clock (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_clock(Clock *c, int *queue_serial)
{
    c->speed = 1.0;
    c->paused = 0;
    c->queue_serial = queue_serial;
    set_clock(c, NAN, -1);
}