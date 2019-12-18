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
 int /*<<< orphan*/  DFISNAN (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DFISSIGNED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DFISZERO (int /*<<< orphan*/  const*) ; 

uInt decFloatIsPositive(const decFloat *df) {
  return !DFISSIGNED(df) && !DFISZERO(df) && !DFISNAN(df);
  }