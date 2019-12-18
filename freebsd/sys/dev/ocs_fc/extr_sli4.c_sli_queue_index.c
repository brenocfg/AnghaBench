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
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_3__ {int index; } ;
typedef  TYPE_1__ sli4_queue_t ;
typedef  int int32_t ;

/* Variables and functions */

int32_t
sli_queue_index(sli4_t *sli4, sli4_queue_t *q)
{

	if (q) {
		return q->index;
	} else {
		return -1;
	}
}