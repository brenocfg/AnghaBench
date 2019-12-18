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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ptunit_result {int dummy; } ;
struct pt_config {int /*<<< orphan*/  addr_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 unsigned long long pt_addr_cfg_disabled ; 
 int /*<<< orphan*/  pt_config_init (struct pt_config*) ; 
 int /*<<< orphan*/  pt_filter_addr_a (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_filter_addr_b (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_filter_addr_cfg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static struct ptunit_result addr_filter_oob(uint8_t filter)
{
	struct pt_config config;
	uint64_t addr_a, addr_b;
	uint32_t addr_cfg;

	pt_config_init(&config);

	memset(&config.addr_filter, 0xcc, sizeof(config.addr_filter));

	addr_cfg = pt_filter_addr_cfg(&config.addr_filter, filter);
	ptu_uint_eq(addr_cfg, pt_addr_cfg_disabled);

	addr_a = pt_filter_addr_a(&config.addr_filter, filter);
	ptu_uint_eq(addr_a, 0ull);

	addr_b = pt_filter_addr_b(&config.addr_filter, filter);
	ptu_uint_eq(addr_b, 0ull);

	return ptu_passed();
}