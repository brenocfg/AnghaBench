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
typedef  int u32 ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int HDR_SHARED ; 
 int HDR_START_IDX_SHIFT ; 
 int /*<<< orphan*/  PRINT_POS ; 
 int /*<<< orphan*/  append_ptr (int* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_job_desc (int* const,int) ; 

__attribute__((used)) static inline void init_job_desc_shared(u32 * const desc, dma_addr_t ptr,
					int len, u32 options)
{
	PRINT_POS;
	init_job_desc(desc, HDR_SHARED | options |
		      (len << HDR_START_IDX_SHIFT));
	append_ptr(desc, ptr);
}