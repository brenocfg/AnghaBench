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
struct rb153_cf_info {scalar_t__ frozen; } ;
struct ata_port {TYPE_1__* host; } ;
struct TYPE_2__ {struct rb153_cf_info* private_data; } ;

/* Variables and functions */

__attribute__((used)) static void rb153_pata_thaw(struct ata_port *ap)
{
	struct rb153_cf_info *info = ap->host->private_data;

	info->frozen = 0;
}