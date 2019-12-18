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

/* Variables and functions */
 scalar_t__ CPU_LOONGSON3 ; 
 void* blast_scache128_node ; 
 void* blast_scache16_node ; 
 void* blast_scache32_node ; 
 void* blast_scache64_node ; 
 scalar_t__ cache_noop ; 
 unsigned long cpu_scache_line_size () ; 
 scalar_t__ current_cpu_type () ; 
 void* r4k_blast_scache_node ; 

__attribute__((used)) static void r4k_blast_scache_node_setup(void)
{
	unsigned long sc_lsize = cpu_scache_line_size();

	if (current_cpu_type() != CPU_LOONGSON3)
		r4k_blast_scache_node = (void *)cache_noop;
	else if (sc_lsize == 16)
		r4k_blast_scache_node = blast_scache16_node;
	else if (sc_lsize == 32)
		r4k_blast_scache_node = blast_scache32_node;
	else if (sc_lsize == 64)
		r4k_blast_scache_node = blast_scache64_node;
	else if (sc_lsize == 128)
		r4k_blast_scache_node = blast_scache128_node;
}