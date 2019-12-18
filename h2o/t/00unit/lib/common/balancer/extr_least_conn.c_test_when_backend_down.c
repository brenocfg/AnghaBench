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
typedef  int /*<<< orphan*/  h2o_socketpool_target_vector_t ;
typedef  int /*<<< orphan*/  h2o_balancer_t ;

/* Variables and functions */
 int /*<<< orphan*/  destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_targets (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_targets (int) ; 
 int /*<<< orphan*/ * h2o_balancer_create_lc () ; 
 int /*<<< orphan*/  ok (int) ; 
 size_t selector (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_when_backend_down(void)
{
    h2o_socketpool_target_vector_t targets = gen_targets(10);
    char tried[10] = {0};
    size_t i;
    size_t selected;
    h2o_balancer_t *balancer;

    balancer = h2o_balancer_create_lc();

    for (i = 0; i < 10; i++) {
        selected = selector(balancer, &targets, tried);
        ok(selected >= 0 && selected < 10);
        ok(!tried[selected]);
        tried[selected] = 1;
    }

    free_targets(&targets);
    destroy(balancer);
}