#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num; TYPE_1__* string; } ;
struct chat {TYPE_2__ abort; int /*<<< orphan*/  timeout; int /*<<< orphan*/  pause; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_Stop (int /*<<< orphan*/ *) ; 

void
chat_Finish(struct chat *c)
{
  timer_Stop(&c->pause);
  timer_Stop(&c->timeout);
  while (c->abort.num)
    free(c->abort.string[--c->abort.num].data);
  c->abort.num = 0;
}