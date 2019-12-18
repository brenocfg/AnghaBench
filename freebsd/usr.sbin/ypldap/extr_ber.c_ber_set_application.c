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
struct ber {unsigned long (* br_application ) (struct ber_element*) ;} ;

/* Variables and functions */

void
ber_set_application(struct ber *b, unsigned long (*cb)(struct ber_element *))
{
	b->br_application = cb;
}