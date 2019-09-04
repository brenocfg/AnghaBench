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
struct TYPE_3__ {int /*<<< orphan*/  tid; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentThreadId () ; 

pthread_t pthread_self(void)
{
	pthread_t t = { NULL };
	t.tid = GetCurrentThreadId();
	return t;
}