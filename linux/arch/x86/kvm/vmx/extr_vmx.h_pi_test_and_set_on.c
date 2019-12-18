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
struct pi_desc {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  POSTED_INTR_ON ; 
 int test_and_set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static inline bool pi_test_and_set_on(struct pi_desc *pi_desc)
{
	return test_and_set_bit(POSTED_INTR_ON,
			(unsigned long *)&pi_desc->control);
}