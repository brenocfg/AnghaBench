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
struct icl_pdu {int ip_data_len; } ;

/* Variables and functions */

__attribute__((used)) static size_t
icl_pdu_padding(const struct icl_pdu *ip)
{

	if ((ip->ip_data_len % 4) != 0)
		return (4 - (ip->ip_data_len % 4));

	return (0);
}