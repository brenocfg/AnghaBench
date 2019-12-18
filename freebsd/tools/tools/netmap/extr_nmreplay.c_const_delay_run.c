#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct _qs {int /*<<< orphan*/  cur_delay; } ;
struct _cfg {int /*<<< orphan*/ * d; } ;

/* Variables and functions */

__attribute__((used)) static int
const_delay_run(struct _qs *q, struct _cfg *arg)
{
	q->cur_delay = arg->d[0]; /* the delay */
	return 0;
}