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
struct rc_dec {scalar_t__ in_pos; scalar_t__ in_limit; } ;

/* Variables and functions */

__attribute__((used)) static inline char rc_limit_exceeded(const struct rc_dec *rc)
{
	return rc->in_pos > rc->in_limit;
}