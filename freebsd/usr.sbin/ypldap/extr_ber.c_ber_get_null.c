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
struct ber_element {scalar_t__ be_encoding; } ;

/* Variables and functions */
 scalar_t__ BER_TYPE_NULL ; 

int
ber_get_null(struct ber_element *elm)
{
	if (elm->be_encoding != BER_TYPE_NULL)
		return -1;

	return 0;
}