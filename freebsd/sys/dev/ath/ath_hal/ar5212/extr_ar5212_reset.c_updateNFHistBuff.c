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
struct ar5212NfCalHist {size_t currIndex; int /*<<< orphan*/ * nfCalBuffer; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 size_t AR512_NF_CAL_HIST_MAX ; 

__attribute__((used)) static __inline void
updateNFHistBuff(struct ar5212NfCalHist *h, int16_t nf)
{
 	h->nfCalBuffer[h->currIndex] = nf;
     	if (++h->currIndex >= AR512_NF_CAL_HIST_MAX)
		h->currIndex = 0;
}