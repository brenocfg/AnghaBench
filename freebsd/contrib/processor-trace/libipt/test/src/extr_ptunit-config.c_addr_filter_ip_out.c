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
struct ptunit_result {int dummy; } ;
struct TYPE_4__ {void* addr3_cfg; void* addr1_cfg; } ;
struct TYPE_5__ {TYPE_1__ ctl; } ;
struct TYPE_6__ {int addr1_a; int addr1_b; int addr3_a; int addr3_b; TYPE_2__ config; } ;
struct pt_config {TYPE_3__ addr_filter; } ;

/* Variables and functions */
 void* pt_addr_cfg_filter ; 
 int /*<<< orphan*/  pt_config_init (struct pt_config*) ; 
 int pt_filter_addr_check (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result addr_filter_ip_out(void)
{
	struct pt_config config;
	int status;

	pt_config_init(&config);
	config.addr_filter.config.ctl.addr1_cfg = pt_addr_cfg_filter;
	config.addr_filter.addr1_a = 0xa000;
	config.addr_filter.addr1_b = 0xb000;
	config.addr_filter.config.ctl.addr3_cfg = pt_addr_cfg_filter;
	config.addr_filter.addr3_a = 0x10a000;
	config.addr_filter.addr3_b = 0x10b000;

	status = pt_filter_addr_check(&config.addr_filter, 0xfff);
	ptu_int_eq(status, 0);

	status = pt_filter_addr_check(&config.addr_filter, 0xb001);
	ptu_int_eq(status, 0);

	status = pt_filter_addr_check(&config.addr_filter, 0x100fff);
	ptu_int_eq(status, 0);

	status = pt_filter_addr_check(&config.addr_filter, 0x10b001);
	ptu_int_eq(status, 0);

	return ptu_passed();
}