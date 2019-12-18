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
struct hv_24x7_event_data {scalar_t__ remainder; int /*<<< orphan*/  event_name_len; } ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *event_name(struct hv_24x7_event_data *ev, int *len)
{
	*len = be16_to_cpu(ev->event_name_len) - 2;
	return (char *)ev->remainder;
}