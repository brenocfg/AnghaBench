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
struct microcode_header_intel {int /*<<< orphan*/  pf; int /*<<< orphan*/  sig; } ;
struct extended_sigtable {int count; } ;
struct extended_signature {int /*<<< orphan*/  pf; int /*<<< orphan*/  sig; } ;

/* Variables and functions */
 int EXT_HEADER_SIZE ; 
 scalar_t__ MC_HEADER_SIZE ; 
 scalar_t__ cpu_signatures_match (unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_datasize (struct microcode_header_intel*) ; 
 scalar_t__ get_totalsize (struct microcode_header_intel*) ; 

__attribute__((used)) static int find_matching_signature(void *mc, unsigned int csig, int cpf)
{
	struct microcode_header_intel *mc_hdr = mc;
	struct extended_sigtable *ext_hdr;
	struct extended_signature *ext_sig;
	int i;

	if (cpu_signatures_match(csig, cpf, mc_hdr->sig, mc_hdr->pf))
		return 1;

	/* Look for ext. headers: */
	if (get_totalsize(mc_hdr) <= get_datasize(mc_hdr) + MC_HEADER_SIZE)
		return 0;

	ext_hdr = mc + get_datasize(mc_hdr) + MC_HEADER_SIZE;
	ext_sig = (void *)ext_hdr + EXT_HEADER_SIZE;

	for (i = 0; i < ext_hdr->count; i++) {
		if (cpu_signatures_match(csig, cpf, ext_sig->sig, ext_sig->pf))
			return 1;
		ext_sig++;
	}
	return 0;
}