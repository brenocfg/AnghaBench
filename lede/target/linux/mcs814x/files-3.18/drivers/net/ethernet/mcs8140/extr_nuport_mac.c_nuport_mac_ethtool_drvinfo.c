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
struct net_device {int dummy; } ;
struct ethtool_drvinfo {scalar_t__ eedump_len; scalar_t__ regdump_len; scalar_t__ testinfo_len; scalar_t__ n_stats; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void nuport_mac_ethtool_drvinfo(struct net_device *dev,
					struct ethtool_drvinfo *info)
{
	strncpy(info->driver, "nuport-mac", sizeof(info->driver));
	strncpy(info->version, "0.1", sizeof(info->version));
	strncpy(info->fw_version, "N/A", sizeof(info->fw_version));
	strncpy(info->bus_info, "internal", sizeof(info->bus_info));
	info->n_stats = 0;
	info->testinfo_len = 0;
	info->regdump_len = 0;
	info->eedump_len = 0;
}