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
struct rfc2734_header {int w0; int /*<<< orphan*/  w1; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFC2374_HDR_FIRSTFRAG ; 
 int fwnet_set_hdr_dg_size (unsigned int) ; 
 int /*<<< orphan*/  fwnet_set_hdr_dgl (unsigned int) ; 
 int fwnet_set_hdr_ether_type (unsigned int) ; 
 int fwnet_set_hdr_lf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void fwnet_make_ff_hdr(struct rfc2734_header *hdr,
		unsigned ether_type, unsigned dg_size, unsigned dgl)
{
	hdr->w0 = fwnet_set_hdr_lf(RFC2374_HDR_FIRSTFRAG)
		  | fwnet_set_hdr_dg_size(dg_size)
		  | fwnet_set_hdr_ether_type(ether_type);
	hdr->w1 = fwnet_set_hdr_dgl(dgl);
}