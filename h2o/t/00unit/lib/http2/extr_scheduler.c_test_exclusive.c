#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * member_0; } ;
struct TYPE_4__ {TYPE_2__ member_0; } ;
struct TYPE_6__ {char* member_1; int member_2; int /*<<< orphan*/  ref; scalar_t__ still_is_active; int /*<<< orphan*/  member_3; TYPE_1__ member_0; } ;
typedef  TYPE_3__ node_t ;
typedef  int /*<<< orphan*/  h2o_http2_scheduler_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_http2_scheduler_activate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iterate_cb ; 
 int max_cnt ; 
 int /*<<< orphan*/  ok (int) ; 
 char* output ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void test_exclusive(void)
{
    h2o_http2_scheduler_node_t scheduler;
    node_t nodeA = {{{NULL}}, "A", 1, 0};
    node_t nodeB = {{{NULL}}, "B", 1, 0};
    node_t nodeC = {{{NULL}}, "C", 1, 0};

    h2o_http2_scheduler_init(&scheduler);

    /*
     * root      root
     *  /\        |
     * A  B  =>   C
     *            |\
     *            A B
     */

    /* open A & B */
    h2o_http2_scheduler_open(&nodeA.ref, &scheduler, 32, 0);
    h2o_http2_scheduler_activate(&nodeA.ref);
    h2o_http2_scheduler_open(&nodeB.ref, &scheduler, 32, 0);
    h2o_http2_scheduler_activate(&nodeB.ref);

    output[0] = '\0';
    max_cnt = 5;
    h2o_http2_scheduler_run(&scheduler, iterate_cb, NULL);
    ok(strcmp(output, "A,B,A,B,A") == 0);

    /* add C as an exclusive */
    h2o_http2_scheduler_open(&nodeC.ref, &scheduler, 12, 1);

    /* should get A & B since C is inactive */
    output[0] = '\0';
    max_cnt = 5;
    h2o_http2_scheduler_run(&scheduler, iterate_cb, NULL);
    ok(strcmp(output, "A,B,A,B,A") == 0); /* under current impl, moving the deps causes them to be ordered using _all_ref */

    /* should see C once it is activated */
    h2o_http2_scheduler_activate(&nodeC.ref);
    output[0] = '\0';
    max_cnt = 5;
    h2o_http2_scheduler_run(&scheduler, iterate_cb, NULL);
    ok(strcmp(output, "C,C,C,C,C") == 0);

    /* eventually disabling C should show A and B */
    nodeC.still_is_active = 0;
    output[0] = '\0';
    max_cnt = 5;
    h2o_http2_scheduler_run(&scheduler, iterate_cb, NULL);
    ok(strcmp(output, "C,B,A,B,A") == 0);

    h2o_http2_scheduler_close(&nodeA.ref);
    h2o_http2_scheduler_close(&nodeB.ref);
    h2o_http2_scheduler_close(&nodeC.ref);
    h2o_http2_scheduler_dispose(&scheduler);
}