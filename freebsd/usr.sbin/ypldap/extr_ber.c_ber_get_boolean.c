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
struct ber_element {scalar_t__ be_encoding; scalar_t__ be_numeric; } ;

/* Variables and functions */
 scalar_t__ BER_TYPE_BOOLEAN ; 

int
ber_get_boolean(struct ber_element *elm, int *b)
{
	if (elm->be_encoding != BER_TYPE_BOOLEAN)
		return -1;

	*b = !(elm->be_numeric == 0);
	return 0;
}