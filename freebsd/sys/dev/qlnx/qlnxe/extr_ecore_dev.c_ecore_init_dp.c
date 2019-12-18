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
typedef  void* u8 ;
typedef  size_t u32 ;
struct ecore_hwfn {size_t dp_module; void* dp_ctx; void* dp_level; } ;
struct ecore_dev {size_t dp_module; struct ecore_hwfn* hwfns; void* dp_ctx; void* dp_level; } ;

/* Variables and functions */
 size_t MAX_HWFNS_PER_DEVICE ; 

void ecore_init_dp(struct ecore_dev	*p_dev,
		   u32			dp_module,
		   u8			dp_level,
		   void		 *dp_ctx)
{
	u32 i;

	p_dev->dp_level = dp_level;
	p_dev->dp_module = dp_module;
	p_dev->dp_ctx = dp_ctx;
	for (i = 0; i < MAX_HWFNS_PER_DEVICE; i++) {
		struct ecore_hwfn *p_hwfn = &p_dev->hwfns[i];

		p_hwfn->dp_level = dp_level;
		p_hwfn->dp_module = dp_module;
		p_hwfn->dp_ctx = dp_ctx;
	}
}