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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_char ;
struct dccp_hdr_ext {int /*<<< orphan*/  dccph_seq; } ;
struct dccp_hdr {int /*<<< orphan*/  dccph_seq; } ;

/* Variables and functions */
 scalar_t__ DCCPH_X (struct dccp_hdr const*) ; 
 int /*<<< orphan*/  EXTRACT_24BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXTRACT_48BITS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t dccp_seqno(const u_char *bp)
{
	const struct dccp_hdr *dh = (const struct dccp_hdr *)bp;
	uint64_t seqno;

	if (DCCPH_X(dh) != 0) {
		const struct dccp_hdr_ext *dhx = (const struct dccp_hdr_ext *)bp;
		seqno = EXTRACT_48BITS(dhx->dccph_seq);
	} else {
		seqno = EXTRACT_24BITS(dh->dccph_seq);
	}

	return seqno;
}