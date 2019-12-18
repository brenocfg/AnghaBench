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
 int /*<<< orphan*/ * decCanonical (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  decFloatCopyAbs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * decFloatMin (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ decNumCompare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

decFloat * decFloatMinMag(decFloat *result,
                       const decFloat *dfl, const decFloat *dfr,
                       decContext *set) {
  Int comp;
  decFloat absl, absr;
  if (DFISNAN(dfl) || DFISNAN(dfr)) return decFloatMin(result, dfl, dfr, set);

  decFloatCopyAbs(&absl, dfl);
  decFloatCopyAbs(&absr, dfr);
  comp=decNumCompare(&absl, &absr, 0);
  if (comp<0) return decCanonical(result, dfl);
  if (comp>0) return decCanonical(result, dfr);
  return decFloatMin(result, dfl, dfr, set);
  }