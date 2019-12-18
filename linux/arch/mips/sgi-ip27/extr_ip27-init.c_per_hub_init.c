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
struct hub_data {int /*<<< orphan*/  h_cpus; } ;
typedef  int /*<<< orphan*/  nasid_t ;
typedef  scalar_t__ cnodeid_t ;

/* Variables and functions */
 scalar_t__ CKSEG0 ; 
 int /*<<< orphan*/  COMPACT_TO_NASID_NODEID (scalar_t__) ; 
 int /*<<< orphan*/  IIO_ICTO ; 
 int /*<<< orphan*/  IIO_ICTP ; 
 int /*<<< orphan*/  REMOTE_HUB_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __flush_cache_all () ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ get_compact_nodeid () ; 
 struct hub_data* hub_data (scalar_t__) ; 
 int /*<<< orphan*/  hub_init_mask ; 
 int /*<<< orphan*/  hub_rtc_init (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ test_and_set_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void per_hub_init(cnodeid_t cnode)
{
	struct hub_data *hub = hub_data(cnode);
	nasid_t nasid = COMPACT_TO_NASID_NODEID(cnode);

	cpumask_set_cpu(smp_processor_id(), &hub->h_cpus);

	if (test_and_set_bit(cnode, hub_init_mask))
		return;
	/*
	 * Set CRB timeout at 5ms, (< PI timeout of 10ms)
	 */
	REMOTE_HUB_S(nasid, IIO_ICTP, 0x800);
	REMOTE_HUB_S(nasid, IIO_ICTO, 0xff);

	hub_rtc_init(cnode);

#ifdef CONFIG_REPLICATE_EXHANDLERS
	/*
	 * If this is not a headless node initialization,
	 * copy over the caliased exception handlers.
	 */
	if (get_compact_nodeid() == cnode) {
		extern char except_vec2_generic, except_vec3_generic;
		extern void build_tlb_refill_handler(void);

		memcpy((void *)(CKSEG0 + 0x100), &except_vec2_generic, 0x80);
		memcpy((void *)(CKSEG0 + 0x180), &except_vec3_generic, 0x80);
		build_tlb_refill_handler();
		memcpy((void *)(CKSEG0 + 0x100), (void *) CKSEG0, 0x80);
		memcpy((void *)(CKSEG0 + 0x180), &except_vec3_generic, 0x100);
		__flush_cache_all();
	}
#endif
}