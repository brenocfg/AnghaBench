#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* tcp; } ;
struct alias_link {TYPE_3__ data; } ;
struct TYPE_4__ {int ack_modified; } ;
struct TYPE_5__ {TYPE_1__ state; } ;

/* Variables and functions */

int
GetAckModified(struct alias_link *lnk)
{
/* See if ACK numbers have been modified */
	return (lnk->data.tcp->state.ack_modified);
}