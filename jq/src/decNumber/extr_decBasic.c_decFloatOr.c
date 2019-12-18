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
typedef  int /*<<< orphan*/  const decFloat ;
typedef  int /*<<< orphan*/  decContext ;

/* Variables and functions */
 int /*<<< orphan*/  DFISCC01 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DFISUINT01 (int /*<<< orphan*/  const*) ; 
 int DFWORD (int /*<<< orphan*/  const*,int) ; 
 int ZEROWORD ; 
 int /*<<< orphan*/  const* decInvalid (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

decFloat * decFloatOr(decFloat *result,
                       const decFloat *dfl, const decFloat *dfr,
                       decContext *set) {
  if (!DFISUINT01(dfl) || !DFISUINT01(dfr)
   || !DFISCC01(dfl)   || !DFISCC01(dfr)) return decInvalid(result, set);
  // the operands are positive finite integers (q=0) with just 0s and 1s
  #if DOUBLE
   DFWORD(result, 0)=ZEROWORD
                   |((DFWORD(dfl, 0) | DFWORD(dfr, 0))&0x04009124);
   DFWORD(result, 1)=(DFWORD(dfl, 1) | DFWORD(dfr, 1))&0x49124491;
  #elif QUAD
   DFWORD(result, 0)=ZEROWORD
                   |((DFWORD(dfl, 0) | DFWORD(dfr, 0))&0x04000912);
   DFWORD(result, 1)=(DFWORD(dfl, 1) | DFWORD(dfr, 1))&0x44912449;
   DFWORD(result, 2)=(DFWORD(dfl, 2) | DFWORD(dfr, 2))&0x12449124;
   DFWORD(result, 3)=(DFWORD(dfl, 3) | DFWORD(dfr, 3))&0x49124491;
  #endif
  return result;
  }