#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  utime; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
struct double_receive {int /*<<< orphan*/  qid; TYPE_1__ PID; } ;

/* Variables and functions */
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct double_receive*) ; 

void dump (struct double_receive *s) {
  vkprintf (2, "DUMP: PID: %u.%d.%d.%d, qid = %lld, %p\n", s->PID.ip, s->PID.port, s->PID.utime, s->PID.pid, s->qid, s);
}