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
typedef  int uint64_t ;
struct TYPE_4__ {int ns; } ;
typedef  TYPE_1__ nstime_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

uint64_t
nstime_divide(const nstime_t *time, const nstime_t *divisor) {
	assert(divisor->ns != 0);

	return time->ns / divisor->ns;
}