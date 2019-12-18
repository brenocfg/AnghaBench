#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  decFloat ;
struct TYPE_4__ {int /*<<< orphan*/  round; } ;
typedef  TYPE_1__ decContext ;

/* Variables and functions */
 int /*<<< orphan*/ * decToIntegral (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ ,int) ; 

decFloat * decFloatToIntegralExact(decFloat *result, const decFloat *df,
                                   decContext *set) {
  return decToIntegral(result, df, set, set->round, 1);}