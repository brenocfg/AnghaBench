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
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *event_long_desc(struct hv_24x7_event_data *ev, int *len)
{
	unsigned nl = be16_to_cpu(ev->event_name_len);
	__be16 *desc_len_ = (__be16 *)(ev->remainder + nl - 2);
	unsigned desc_len = be16_to_cpu(*desc_len_);
	__be16 *long_desc_len = (__be16 *)(ev->remainder + nl + desc_len - 2);

	*len = be16_to_cpu(*long_desc_len) - 2;
	return (char *)ev->remainder + nl + desc_len;
}