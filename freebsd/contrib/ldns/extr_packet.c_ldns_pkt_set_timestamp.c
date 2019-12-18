#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {TYPE_1__ timestamp; } ;
typedef  TYPE_2__ ldns_pkt ;

/* Variables and functions */

void
ldns_pkt_set_timestamp(ldns_pkt *packet, struct timeval timeval)
{
	packet->timestamp.tv_sec = timeval.tv_sec;
	packet->timestamp.tv_usec = timeval.tv_usec;
}