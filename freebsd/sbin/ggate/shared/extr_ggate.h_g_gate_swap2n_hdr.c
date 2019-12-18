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
struct g_gate_hdr {int /*<<< orphan*/  gh_error; void* gh_seq; int /*<<< orphan*/  gh_length; void* gh_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  htobe16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 
 void* htobe64 (void*) ; 

__attribute__((used)) static __inline void
g_gate_swap2n_hdr(struct g_gate_hdr *hdr)
{

	/* Swap only used fields. */
	hdr->gh_offset = htobe64(hdr->gh_offset);
	hdr->gh_length = htobe32(hdr->gh_length);
	hdr->gh_seq = htobe64(hdr->gh_seq);
	hdr->gh_error = htobe16(hdr->gh_error);
}