#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  node; } ;
struct TYPE_8__ {int /*<<< orphan*/ * member_0; } ;
struct TYPE_7__ {TYPE_2__ member_0; } ;
struct TYPE_9__ {char* member_1; int member_2; int still_is_active; TYPE_4__ ref; int /*<<< orphan*/  member_3; TYPE_1__ member_0; } ;
typedef  TYPE_3__ node_t ;
typedef  int /*<<< orphan*/  h2o_http2_scheduler_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_http2_scheduler_activate (TYPE_4__*) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_close (TYPE_4__*) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_open (TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iterate_cb ; 
 int max_cnt ; 
 int /*<<< orphan*/  ok (int) ; 
 char* output ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void test_dependency(void)
{
    h2o_http2_scheduler_node_t root;
    node_t nodeA = {{{NULL}}, "A", 1, 0};
    node_t nodeB = {{{NULL}}, "B", 1, 0};
    node_t nodeC = {{{NULL}}, "C", 1, 0};
    node_t nodeD = {{{NULL}}, "D", 1, 0};

    /*
     * root
     *  /|\
     * A B C
     * |
     * D
     */

    h2o_http2_scheduler_init(&root);
    h2o_http2_scheduler_open(&nodeA.ref, &root, 32, 0);
    h2o_http2_scheduler_activate(&nodeA.ref);
    h2o_http2_scheduler_open(&nodeB.ref, &root, 32, 0);
    h2o_http2_scheduler_activate(&nodeB.ref);
    h2o_http2_scheduler_open(&nodeC.ref, &root, 12, 0);
    h2o_http2_scheduler_activate(&nodeC.ref);
    h2o_http2_scheduler_open(&nodeD.ref, &nodeA.ref.node, 6, 0);
    h2o_http2_scheduler_activate(&nodeD.ref);

    /* should get A and B (and some C) */
    output[0] = '\0';
    max_cnt = 20;
    h2o_http2_scheduler_run(&root, iterate_cb, NULL);
    ok(strcmp(output, "A,B,A,B,C,A,B,A,B,A,B,C,A,B,A,B,C,A,B,A") == 0);

    /* eventually disactivate A, should get D,B (and some C) */
    nodeA.still_is_active = 0;
    output[0] = '\0';
    max_cnt = 20;
    h2o_http2_scheduler_run(&root, iterate_cb, NULL);
    ok(strcmp(output, "B,A,B,C,D,B,D,B,D,B,C,D,B,D,B,C,D,B,D,B") == 0);

    /* eventually disactivate B, should get D only (and some C) */
    nodeB.still_is_active = 0;
    output[0] = '\0';
    max_cnt = 20;
    h2o_http2_scheduler_run(&root, iterate_cb, NULL);
    ok(strcmp(output, "D,B,C,D,D,D,C,D,D,C,D,D,D,C,D,D,C,D,D,D") == 0);

    /* closing A raises D, and the priority becomes D = B > C */
    h2o_http2_scheduler_close(&nodeA.ref);
    h2o_http2_scheduler_activate(&nodeB.ref);
    nodeB.still_is_active = 1;
    output[0] = '\0';
    max_cnt = 20;
    h2o_http2_scheduler_run(&root, iterate_cb, NULL);
    ok(strcmp(output, "D,C,B,D,B,D,B,C,D,B,D,B,D,C,B,D,B,D,B,C") == 0);

    h2o_http2_scheduler_close(&nodeB.ref);
    h2o_http2_scheduler_close(&nodeC.ref);
    h2o_http2_scheduler_close(&nodeD.ref);
    h2o_http2_scheduler_dispose(&root);
}