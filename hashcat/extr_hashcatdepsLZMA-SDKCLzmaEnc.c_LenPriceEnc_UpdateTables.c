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
typedef  int /*<<< orphan*/  CProbPrice ;
typedef  int /*<<< orphan*/  CLenPriceEnc ;
typedef  int /*<<< orphan*/  CLenEnc ;

/* Variables and functions */
 int /*<<< orphan*/  LenPriceEnc_UpdateTable (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void LenPriceEnc_UpdateTables(CLenPriceEnc *p, unsigned numPosStates,
    const CLenEnc *enc,
    const CProbPrice *ProbPrices)
{
  unsigned posState;
  for (posState = 0; posState < numPosStates; posState++)
    LenPriceEnc_UpdateTable(p, posState, enc, ProbPrices);
}