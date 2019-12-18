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
struct TYPE_3__ {int /*<<< orphan*/  (* ra_init_alg ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RANDOM_SEEDED ; 
 int /*<<< orphan*/  READ_RANDOM ; 
 int /*<<< orphan*/  READ_RANDOM_UIO ; 
 TYPE_1__* p_random_alg_context ; 
 TYPE_1__ random_alg_context ; 
 int /*<<< orphan*/  random_infra_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void
random_alg_context_ra_init_alg(void *data)
{

	p_random_alg_context = &random_alg_context;
	p_random_alg_context->ra_init_alg(data);
#if defined(RANDOM_LOADABLE)
	random_infra_init(READ_RANDOM_UIO, READ_RANDOM, IS_RANDOM_SEEDED);
#endif
}