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
struct ttyoutq {scalar_t__ to_end; scalar_t__ to_begin; } ;

/* Variables and functions */

void
ttyoutq_flush(struct ttyoutq *to)
{

	to->to_begin = 0;
	to->to_end = 0;
}