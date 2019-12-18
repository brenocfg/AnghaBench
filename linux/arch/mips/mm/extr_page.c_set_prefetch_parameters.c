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
struct TYPE_2__ {int processor_id; } ;

/* Variables and functions */
#define  CPU_LOONGSON3 136 
#define  CPU_R10000 135 
#define  CPU_R12000 134 
#define  CPU_R14000 133 
#define  CPU_R16000 132 
#define  CPU_R5500 131 
#define  CPU_SB1 130 
#define  CPU_SB1A 129 
#define  CPU_TX49XX 128 
 int /*<<< orphan*/  Pref_Load ; 
 int /*<<< orphan*/  Pref_LoadStreamed ; 
 int /*<<< orphan*/  Pref_PrepareForStore ; 
 int /*<<< orphan*/  Pref_Store ; 
 int /*<<< orphan*/  Pref_StoreStreamed ; 
 int cache_line_size ; 
 int clear_word_size ; 
 int copy_word_size ; 
 int cpu_dcache_line_size () ; 
 scalar_t__ cpu_has_64bit_gp_regs ; 
 scalar_t__ cpu_has_64bit_zero_reg ; 
 scalar_t__ cpu_has_cache_cdex_p ; 
 scalar_t__ cpu_has_cache_cdex_s ; 
 int /*<<< orphan*/  cpu_has_mips_r6 ; 
 scalar_t__ cpu_has_prefetch ; 
 int cpu_scache_line_size () ; 
 TYPE_1__ current_cpu_data ; 
 int const current_cpu_type () ; 
 void* half_clear_loop_size ; 
 void* half_copy_loop_size ; 
 int /*<<< orphan*/  max (int,int) ; 
 void* min (int,int /*<<< orphan*/ ) ; 
 int pref_bias_clear_store ; 
 int pref_bias_copy_load ; 
 int pref_bias_copy_store ; 
 int /*<<< orphan*/  pref_dst_mode ; 
 int /*<<< orphan*/  pref_src_mode ; 

__attribute__((used)) static void set_prefetch_parameters(void)
{
	if (cpu_has_64bit_gp_regs || cpu_has_64bit_zero_reg)
		clear_word_size = 8;
	else
		clear_word_size = 4;

	if (cpu_has_64bit_gp_regs)
		copy_word_size = 8;
	else
		copy_word_size = 4;

	/*
	 * The pref's used here are using "streaming" hints, which cause the
	 * copied data to be kicked out of the cache sooner.  A page copy often
	 * ends up copying a lot more data than is commonly used, so this seems
	 * to make sense in terms of reducing cache pollution, but I've no real
	 * performance data to back this up.
	 */
	if (cpu_has_prefetch) {
		/*
		 * XXX: Most prefetch bias values in here are based on
		 * guesswork.
		 */
		cache_line_size = cpu_dcache_line_size();
		switch (current_cpu_type()) {
		case CPU_R5500:
		case CPU_TX49XX:
			/* These processors only support the Pref_Load. */
			pref_bias_copy_load = 256;
			break;

		case CPU_R10000:
		case CPU_R12000:
		case CPU_R14000:
		case CPU_R16000:
			/*
			 * Those values have been experimentally tuned for an
			 * Origin 200.
			 */
			pref_bias_clear_store = 512;
			pref_bias_copy_load = 256;
			pref_bias_copy_store = 256;
			pref_src_mode = Pref_LoadStreamed;
			pref_dst_mode = Pref_StoreStreamed;
			break;

		case CPU_SB1:
		case CPU_SB1A:
			pref_bias_clear_store = 128;
			pref_bias_copy_load = 128;
			pref_bias_copy_store = 128;
			/*
			 * SB1 pass1 Pref_LoadStreamed/Pref_StoreStreamed
			 * hints are broken.
			 */
			if (current_cpu_type() == CPU_SB1 &&
			    (current_cpu_data.processor_id & 0xff) < 0x02) {
				pref_src_mode = Pref_Load;
				pref_dst_mode = Pref_Store;
			} else {
				pref_src_mode = Pref_LoadStreamed;
				pref_dst_mode = Pref_StoreStreamed;
			}
			break;

		case CPU_LOONGSON3:
			/* Loongson-3 only support the Pref_Load/Pref_Store. */
			pref_bias_clear_store = 128;
			pref_bias_copy_load = 128;
			pref_bias_copy_store = 128;
			pref_src_mode = Pref_Load;
			pref_dst_mode = Pref_Store;
			break;

		default:
			pref_bias_clear_store = 128;
			pref_bias_copy_load = 256;
			pref_bias_copy_store = 128;
			pref_src_mode = Pref_LoadStreamed;
			if (cpu_has_mips_r6)
				/*
				 * Bit 30 (Pref_PrepareForStore) has been
				 * removed from MIPS R6. Use bit 5
				 * (Pref_StoreStreamed).
				 */
				pref_dst_mode = Pref_StoreStreamed;
			else
				pref_dst_mode = Pref_PrepareForStore;
			break;
		}
	} else {
		if (cpu_has_cache_cdex_s)
			cache_line_size = cpu_scache_line_size();
		else if (cpu_has_cache_cdex_p)
			cache_line_size = cpu_dcache_line_size();
	}
	/*
	 * Too much unrolling will overflow the available space in
	 * clear_space_array / copy_page_array.
	 */
	half_clear_loop_size = min(16 * clear_word_size,
				   max(cache_line_size >> 1,
				       4 * clear_word_size));
	half_copy_loop_size = min(16 * copy_word_size,
				  max(cache_line_size >> 1,
				      4 * copy_word_size));
}