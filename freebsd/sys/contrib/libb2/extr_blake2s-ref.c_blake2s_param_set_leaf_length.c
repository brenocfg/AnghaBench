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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  leaf_length; } ;
typedef  TYPE_1__ blake2s_param ;

/* Variables and functions */
 int /*<<< orphan*/  store32 (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline int blake2s_param_set_leaf_length( blake2s_param *P, const uint32_t leaf_length )
{
  store32( &P->leaf_length, leaf_length );
  return 0;
}