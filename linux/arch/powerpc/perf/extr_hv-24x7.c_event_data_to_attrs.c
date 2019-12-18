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
struct hv_24x7_event_data {int /*<<< orphan*/  domain; } ;
struct attribute {int dummy; } ;

/* Variables and functions */
 struct attribute* event_to_attr (unsigned int,struct hv_24x7_event_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int event_data_to_attrs(unsigned ix, struct attribute **attrs,
				   struct hv_24x7_event_data *event, int nonce)
{
	*attrs = event_to_attr(ix, event, event->domain, nonce);
	if (!*attrs)
		return -1;

	return 0;
}