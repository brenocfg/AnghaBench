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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ptunit_result {int dummy; } ;
struct TYPE_6__ {int addr0_cfg; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr_cfg; TYPE_1__ ctl; } ;
struct TYPE_8__ {int addr0_a; int addr0_b; TYPE_2__ config; } ;
struct pt_config {TYPE_3__ addr_filter; } ;

/* Variables and functions */
 int pt_addr_cfg_disabled ; 
 int pt_addr_cfg_filter ; 
 int /*<<< orphan*/  pt_config_init (struct pt_config*) ; 
 int /*<<< orphan*/  pt_filter_addr_a (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_filter_addr_b (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_filter_addr_cfg (TYPE_3__*,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptu_uint_ne (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static struct ptunit_result addr_filter_0(void)
{
	struct pt_config config;
	uint64_t addr_a, addr_b;
	uint32_t addr_cfg;
	uint8_t filter;

	pt_config_init(&config);
	config.addr_filter.config.ctl.addr0_cfg = pt_addr_cfg_filter;
	config.addr_filter.addr0_a = 0xa000ull;
	config.addr_filter.addr0_b = 0xb000ull;

	ptu_uint_ne(config.addr_filter.config.addr_cfg, 0ull);

	addr_cfg = pt_filter_addr_cfg(&config.addr_filter, 0);
	ptu_uint_eq(addr_cfg, pt_addr_cfg_filter);

	addr_a = pt_filter_addr_a(&config.addr_filter, 0);
	ptu_uint_eq(addr_a, 0xa000ull);

	addr_b = pt_filter_addr_b(&config.addr_filter, 0);
	ptu_uint_eq(addr_b, 0xb000ull);

	for (filter = 1; filter < 4; ++filter) {

		addr_cfg = pt_filter_addr_cfg(&config.addr_filter, filter);

		ptu_uint_eq(addr_cfg, pt_addr_cfg_disabled);
	}

	return ptu_passed();
}