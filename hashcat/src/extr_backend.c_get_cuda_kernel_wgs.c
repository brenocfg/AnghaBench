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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  hashcat_ctx_t ;
typedef  int /*<<< orphan*/  CUfunction ;

/* Variables and functions */
 int /*<<< orphan*/  CU_FUNC_ATTRIBUTE_MAX_THREADS_PER_BLOCK ; 
 int hc_cuFuncGetAttribute (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_cuda_kernel_wgs (hashcat_ctx_t *hashcat_ctx, CUfunction function, u32 *result)
{
  int max_threads_per_block;

  if (hc_cuFuncGetAttribute (hashcat_ctx, &max_threads_per_block, CU_FUNC_ATTRIBUTE_MAX_THREADS_PER_BLOCK, function) == -1) return -1;

  *result = (u32) max_threads_per_block;

  return 0;
}