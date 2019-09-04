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
 int /*<<< orphan*/  dump_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_activate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_rebind (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iterate_cb ; 
 int max_cnt ; 
 int /*<<< orphan*/  ok (int) ; 
 char* output ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void test_change_weight(void)
{
    h2o_http2_scheduler_node_t root;
    node_t nodeA = {{{NULL}}, "A", 1, 0};
    node_t nodeB = {{{NULL}}, "B", 1, 0};
    node_t nodeC = {{{NULL}}, "C", 1, 0};

    h2o_http2_scheduler_init(&root);

    /* open them all with priority=16 */
    h2o_http2_scheduler_open(&nodeA.ref, &root, 16, 0);
    h2o_http2_scheduler_activate(&nodeA.ref);
    h2o_http2_scheduler_open(&nodeB.ref, &root, 16, 0);
    h2o_http2_scheduler_activate(&nodeB.ref);
    h2o_http2_scheduler_open(&nodeC.ref, &root, 16, 0);
    h2o_http2_scheduler_activate(&nodeC.ref);
    output[0] = '\0';
    dump_tree(&root);
    ok(strcmp(output, "(A16B16C16)") == 0);

    /* check the output */
    output[0] = '\0';
    max_cnt = 20;
    h2o_http2_scheduler_run(&root, iterate_cb, NULL);
    ok(strcmp(output, "A,B,C,A,B,C,A,B,C,A,B,C,A,B,C,A,B,C,A,B") == 0);

    /* nodeA.priority = 4 */
    h2o_http2_scheduler_rebind(&nodeA.ref, &root, 4, 0);
    output[0] = '\0';
    dump_tree(&root);
    ok(strcmp(output, "(B16C16A4)") == 0);
    output[0] = '\0';
    max_cnt = 20;
    h2o_http2_scheduler_run(&root, iterate_cb, NULL);
    ok(strcmp(output, "C,B,C,B,C,B,C,A,B,C,B,C,B,C,B,C,A,B,C,B") == 0);

    /* eventually disactivate B,C */
    nodeB.still_is_active = 0;
    nodeC.still_is_active = 0;
    output[0] = '\0';
    max_cnt = 10;
    h2o_http2_scheduler_run(&root, iterate_cb, NULL);
    ok(strcmp(output, "C,B,A,A,A,A,A,A,A,A") == 0);

    h2o_http2_scheduler_close(&nodeA.ref);
    h2o_http2_scheduler_close(&nodeB.ref);
    h2o_http2_scheduler_close(&nodeC.ref);
    h2o_http2_scheduler_dispose(&root);
}