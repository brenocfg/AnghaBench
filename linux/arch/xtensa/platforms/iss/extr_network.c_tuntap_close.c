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
struct TYPE_4__ {int fd; } ;
struct TYPE_5__ {TYPE_1__ tuntap; } ;
struct TYPE_6__ {TYPE_2__ info; } ;
struct iss_net_private {TYPE_3__ tp; } ;

/* Variables and functions */
 int /*<<< orphan*/  simc_close (int) ; 

__attribute__((used)) static void tuntap_close(struct iss_net_private *lp)
{
	simc_close(lp->tp.info.tuntap.fd);
	lp->tp.info.tuntap.fd = -1;
}