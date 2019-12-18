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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum cc_cpp_alg { ____Placeholder_cc_cpp_alg } cc_cpp_alg ;

/* Variables and functions */
 int /*<<< orphan*/  CC_CPP_NUM_ALGS ; 
 int /*<<< orphan*/  CC_CPP_NUM_SLOTS ; 
 int array_index_nospec (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** cc_cpp_int_masks ; 

__attribute__((used)) static inline u32 cc_cpp_int_mask(enum cc_cpp_alg alg, int slot)
{
	alg = array_index_nospec(alg, CC_CPP_NUM_ALGS);
	slot = array_index_nospec(slot, CC_CPP_NUM_SLOTS);

	return cc_cpp_int_masks[alg][slot];
}