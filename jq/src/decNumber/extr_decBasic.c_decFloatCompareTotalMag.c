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
typedef  int /*<<< orphan*/  decFloat ;

/* Variables and functions */
 scalar_t__ DFISSIGNED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * decFloatCompareTotal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  decFloatCopyAbs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

decFloat * decFloatCompareTotalMag(decFloat *result,
                                const decFloat *dfl, const decFloat *dfr) {
  decFloat a, b;                        // for copy if needed
  // copy and redirect signed operand(s)
  if (DFISSIGNED(dfl)) {
    decFloatCopyAbs(&a, dfl);
    dfl=&a;
    }
  if (DFISSIGNED(dfr)) {
    decFloatCopyAbs(&b, dfr);
    dfr=&b;
    }
  return decFloatCompareTotal(result, dfl, dfr);
  }