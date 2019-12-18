#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  seen; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ slave ;

/* Variables and functions */
 int /*<<< orphan*/  SLAVE_F_AYT ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
slave_seen(slave *s)
{
    s->flags &= ~SLAVE_F_AYT;
    s->seen = time(NULL);
}