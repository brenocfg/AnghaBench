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
typedef  int uInt ;
typedef  int /*<<< orphan*/  decFloat ;

/* Variables and functions */
 scalar_t__ DFISINF (int /*<<< orphan*/  const*) ; 
 scalar_t__ DFISNAN (int /*<<< orphan*/  const*) ; 
 scalar_t__ DFISSPECIAL (int /*<<< orphan*/  const*) ; 
 scalar_t__ GETEXP (int /*<<< orphan*/  const*) ; 

uInt decFloatSameQuantum(const decFloat *dfl, const decFloat *dfr) {
  if (DFISSPECIAL(dfl) || DFISSPECIAL(dfr)) {
    if (DFISNAN(dfl) && DFISNAN(dfr)) return 1;
    if (DFISINF(dfl) && DFISINF(dfr)) return 1;
    return 0;  // any other special mixture gives false
    }
  if (GETEXP(dfl)==GETEXP(dfr)) return 1; // biased exponents match
  return 0;
  }