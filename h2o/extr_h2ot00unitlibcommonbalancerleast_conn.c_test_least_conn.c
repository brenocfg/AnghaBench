#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t size; TYPE_2__** entries; } ;
typedef  TYPE_3__ h2o_socketpool_target_vector_t ;
typedef  int /*<<< orphan*/  h2o_balancer_t ;
struct TYPE_8__ {int /*<<< orphan*/  leased_count; } ;
struct TYPE_9__ {TYPE_1__ _shared; } ;

/* Variables and functions */
 int check_if_acceptable (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_targets (TYPE_3__*) ; 
 TYPE_3__ gen_targets (int) ; 
 int /*<<< orphan*/ * h2o_balancer_create_lc () ; 
 int /*<<< orphan*/  ok (int) ; 
 size_t selector (int /*<<< orphan*/ *,TYPE_3__*,char*) ; 

__attribute__((used)) static void test_least_conn(void)
{
    h2o_socketpool_target_vector_t targets = gen_targets(10);
    size_t i, selected;
    char tried[10] = {0};
    int check_result = 1;
    h2o_balancer_t *balancer;

    balancer = h2o_balancer_create_lc();

    for (i = 0; i < 10000; i++) {
        selected = selector(balancer, &targets, tried);
        if (selected > 10) {
            ok(selected >= 0 && selected < targets.size);
            goto Done;
        }
        check_result = check_if_acceptable(&targets, selected);
        if (check_result == -1) {
            ok(!check_result);
            goto Done;
        }
        targets.entries[selected]->_shared.leased_count++;
    }
    ok(!check_result);

Done:
    free_targets(&targets);
    destroy(balancer);
}