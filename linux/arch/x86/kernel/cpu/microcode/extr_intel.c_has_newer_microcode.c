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
struct microcode_header_intel {int rev; } ;

/* Variables and functions */
 int find_matching_signature (void*,unsigned int,int) ; 

__attribute__((used)) static int has_newer_microcode(void *mc, unsigned int csig, int cpf, int new_rev)
{
	struct microcode_header_intel *mc_hdr = mc;

	if (mc_hdr->rev <= new_rev)
		return 0;

	return find_matching_signature(mc, csig, cpf);
}