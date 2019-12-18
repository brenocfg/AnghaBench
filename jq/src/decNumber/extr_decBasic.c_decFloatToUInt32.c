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
typedef  int /*<<< orphan*/  uInt ;
typedef  enum rounding { ____Placeholder_rounding } rounding ;
typedef  int /*<<< orphan*/  decFloat ;
typedef  int /*<<< orphan*/  decContext ;

/* Variables and functions */
 int /*<<< orphan*/  decToInt32 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

uInt decFloatToUInt32(const decFloat *df, decContext *set,
                      enum rounding round) {
  return decToInt32(df, set, round, 0, 1);}