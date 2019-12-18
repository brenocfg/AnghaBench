#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  inner_length; } ;
typedef  TYPE_1__ blake2s_param ;

/* Variables and functions */

__attribute__((used)) static inline int blake2s_param_set_inner_length( blake2s_param *P, const uint8_t inner_length )
{
  P->inner_length = inner_length;
  return 0;
}