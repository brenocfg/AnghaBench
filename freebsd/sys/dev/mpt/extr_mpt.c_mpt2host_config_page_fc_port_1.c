#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  High; int /*<<< orphan*/  Low; } ;
struct TYPE_3__ {int /*<<< orphan*/  High; int /*<<< orphan*/  Low; } ;
typedef  int /*<<< orphan*/  CONFIG_PAGE_FC_PORT_1 ;

/* Variables and functions */
 int /*<<< orphan*/  Flags ; 
 int /*<<< orphan*/  MPT_2_HOST32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ NoSEEPROMWWNN ; 
 TYPE_1__ NoSEEPROMWWPN ; 

void
mpt2host_config_page_fc_port_1(CONFIG_PAGE_FC_PORT_1 *fp1)
{

	MPT_2_HOST32(fp1, Flags);
	MPT_2_HOST32(fp1, NoSEEPROMWWNN.Low);
	MPT_2_HOST32(fp1, NoSEEPROMWWNN.High);
	MPT_2_HOST32(fp1, NoSEEPROMWWPN.Low);
	MPT_2_HOST32(fp1, NoSEEPROMWWPN.High);
}