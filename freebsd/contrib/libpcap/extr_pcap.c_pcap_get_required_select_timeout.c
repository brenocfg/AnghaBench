#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct TYPE_3__ {struct timeval* required_select_timeout; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */

struct timeval *
pcap_get_required_select_timeout(pcap_t *p)
{
	return (p->required_select_timeout);
}