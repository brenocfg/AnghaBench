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
struct mem_ctl_info {struct i5100_priv* pvt_info; } ;
struct i5100_priv {TYPE_1__** mtr; } ;
struct TYPE_2__ {unsigned int numcol; unsigned int numrow; unsigned int numbank; int /*<<< orphan*/  present; } ;

/* Variables and functions */
 unsigned int I5100_DIMM_ADDR_LINES ; 
 unsigned long long PAGE_SIZE ; 
 unsigned int i5100_csrow_to_chan (struct mem_ctl_info*,unsigned int) ; 
 unsigned int i5100_csrow_to_rank (struct mem_ctl_info*,unsigned int) ; 

__attribute__((used)) static unsigned long i5100_npages(struct mem_ctl_info *mci, unsigned int csrow)
{
	struct i5100_priv *priv = mci->pvt_info;
	const unsigned int chan_rank = i5100_csrow_to_rank(mci, csrow);
	const unsigned int chan = i5100_csrow_to_chan(mci, csrow);
	unsigned addr_lines;

	/* dimm present? */
	if (!priv->mtr[chan][chan_rank].present)
		return 0ULL;

	addr_lines =
		I5100_DIMM_ADDR_LINES +
		priv->mtr[chan][chan_rank].numcol +
		priv->mtr[chan][chan_rank].numrow +
		priv->mtr[chan][chan_rank].numbank;

	return (unsigned long)
		((unsigned long long) (1ULL << addr_lines) / PAGE_SIZE);
}