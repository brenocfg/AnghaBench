#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ptunit_result {int dummy; } ;
struct TYPE_6__ {int addr1_cfg; int addr3_cfg; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr_cfg; TYPE_1__ ctl; } ;
struct TYPE_8__ {int addr1_a; int addr1_b; int addr3_a; int addr3_b; TYPE_2__ config; } ;
struct pt_config {TYPE_3__ addr_filter; } ;

/* Variables and functions */
 int pt_addr_cfg_disabled ; 
 int pt_addr_cfg_filter ; 
 int pt_addr_cfg_stop ; 
 int /*<<< orphan*/  pt_config_init (struct pt_config*) ; 
 int /*<<< orphan*/  pt_filter_addr_a (TYPE_3__*,int) ; 
 int /*<<< orphan*/  pt_filter_addr_b (TYPE_3__*,int) ; 
 int /*<<< orphan*/  pt_filter_addr_cfg (TYPE_3__*,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptu_uint_ne (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static struct ptunit_result addr_filter_1_3(void)
{
	struct pt_config config;
	uint64_t addr_a, addr_b;
	uint32_t addr_cfg;

	pt_config_init(&config);
	config.addr_filter.config.ctl.addr1_cfg = pt_addr_cfg_filter;
	config.addr_filter.addr1_a = 0xa000ull;
	config.addr_filter.addr1_b = 0xb000ull;
	config.addr_filter.config.ctl.addr3_cfg = pt_addr_cfg_stop;
	config.addr_filter.addr3_a = 0x100a000ull;
	config.addr_filter.addr3_b = 0x100b000ull;

	ptu_uint_ne(config.addr_filter.config.addr_cfg, 0ull);

	addr_cfg = pt_filter_addr_cfg(&config.addr_filter, 0);
	ptu_uint_eq(addr_cfg, pt_addr_cfg_disabled);

	addr_cfg = pt_filter_addr_cfg(&config.addr_filter, 1);
	ptu_uint_eq(addr_cfg, pt_addr_cfg_filter);

	addr_a = pt_filter_addr_a(&config.addr_filter, 1);
	ptu_uint_eq(addr_a, 0xa000ull);

	addr_b = pt_filter_addr_b(&config.addr_filter, 1);
	ptu_uint_eq(addr_b, 0xb000ull);

	addr_cfg = pt_filter_addr_cfg(&config.addr_filter, 2);
	ptu_uint_eq(addr_cfg, pt_addr_cfg_disabled);

	addr_cfg = pt_filter_addr_cfg(&config.addr_filter, 3);
	ptu_uint_eq(addr_cfg, pt_addr_cfg_stop);

	addr_a = pt_filter_addr_a(&config.addr_filter, 3);
	ptu_uint_eq(addr_a, 0x100a000ull);

	addr_b = pt_filter_addr_b(&config.addr_filter, 3);
	ptu_uint_eq(addr_b, 0x100b000ull);

	return ptu_passed();
}