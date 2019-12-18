#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* ra_deinit_alg ) (void*) ;} ;

/* Variables and functions */
 TYPE_1__* p_random_alg_context ; 
 int /*<<< orphan*/  random_infra_uninit () ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void
random_alg_context_ra_deinit_alg(void *data)
{

#if defined(RANDOM_LOADABLE)
	random_infra_uninit();
#endif
	p_random_alg_context->ra_deinit_alg(data);
	p_random_alg_context = NULL;
}