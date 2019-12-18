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
typedef  int /*<<< orphan*/  decContext ;
typedef  scalar_t__ Int ;

/* Variables and functions */
 scalar_t__ DFISNAN (int /*<<< orphan*/  const*) ; 
 scalar_t__ DFISSNAN (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * decCanonical (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * decNaNs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ decNumCompare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

decFloat * decFloatMin(decFloat *result,
                       const decFloat *dfl, const decFloat *dfr,
                       decContext *set) {
  Int comp;
  if (DFISNAN(dfl)) {
    // sNaN or both NaNs leads to normal NaN processing
    if (DFISNAN(dfr) || DFISSNAN(dfl)) return decNaNs(result, dfl, dfr, set);
    return decCanonical(result, dfr);        // RHS is numeric
    }
  if (DFISNAN(dfr)) {
    // sNaN leads to normal NaN processing (both NaN handled above)
    if (DFISSNAN(dfr)) return decNaNs(result, dfl, dfr, set);
    return decCanonical(result, dfl);        // LHS is numeric
    }
  // Both operands are numeric; numeric comparison needed -- use
  // total order for a well-defined choice (and +0 > -0)
  comp=decNumCompare(dfl, dfr, 1);
  if (comp<=0) return decCanonical(result, dfl);
  return decCanonical(result, dfr);
  }