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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ecma_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  ecma_number_unpack (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t
ecma_number_get_fraction_field (ecma_number_t num) /**< ecma-number */
{
  uint64_t fraction;

  ecma_number_unpack (num, NULL, NULL, &fraction);

  return fraction;
}