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
typedef  int u32 ;
struct sh_dmae_pdata {int ts_shift_num; int* ts_shift; int ts_low_shift; int ts_low_mask; int ts_high_shift; int ts_high_mask; } ;
struct sh_dmae_device {struct sh_dmae_pdata* pdata; } ;
struct sh_dmae_chan {int dummy; } ;

/* Variables and functions */
 struct sh_dmae_device* to_sh_dev (struct sh_dmae_chan*) ; 

__attribute__((used)) static u32 log2size_to_chcr(struct sh_dmae_chan *sh_chan, int l2size)
{
	struct sh_dmae_device *shdev = to_sh_dev(sh_chan);
	const struct sh_dmae_pdata *pdata = shdev->pdata;
	int i;

	for (i = 0; i < pdata->ts_shift_num; i++)
		if (pdata->ts_shift[i] == l2size)
			break;

	if (i == pdata->ts_shift_num)
		i = 0;

	return ((i << pdata->ts_low_shift) & pdata->ts_low_mask) |
		((i << pdata->ts_high_shift) & pdata->ts_high_mask);
}