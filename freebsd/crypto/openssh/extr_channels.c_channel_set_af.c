#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ssh {TYPE_1__* chanctxt; } ;
struct TYPE_2__ {int IPv4or6; } ;

/* Variables and functions */

void
channel_set_af(struct ssh *ssh, int af)
{
	ssh->chanctxt->IPv4or6 = af;
}