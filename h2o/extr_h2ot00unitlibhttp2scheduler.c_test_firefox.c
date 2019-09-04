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
struct TYPE_9__ {char* member_1; int member_2; TYPE_4__ ref; scalar_t__ still_is_active; int /*<<< orphan*/  member_3; TYPE_1__ member_0; } ;
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

__attribute__((used)) static void test_firefox(void)
{
    /*
     * firefox sends something like below
     *
     * PRIORITY: id:3, dependency:0, weight: 201
     * PRIORITY: id:5, dependency:0, weight: 101
     * PRIORITY: id:7, dependency:0, weight: 1
     * PRIORITY: id:9, dependency:7, weight: 1
     * PRIORITY: id:11, dependency:3, weight: 1
     * HEADERS: id:13, dependency:11, weight: 22
     * HEADERS: id:15, dependency:3, weight: 22
     * HEADERS: id:17, dependency:3, weight: 22
     */
    h2o_http2_scheduler_node_t root;
    node_t g1 = {{{NULL}}, "g1", 0, 0};
    node_t g2 = {{{NULL}}, "g2", 0, 0};
    node_t g3 = {{{NULL}}, "g3", 0, 0};
    node_t g4 = {{{NULL}}, "g4", 0, 0};
    node_t g5 = {{{NULL}}, "g5", 0, 0};
    node_t r1 = {{{NULL}}, "r1", 1, 0};
    node_t r2 = {{{NULL}}, "r2", 1, 0};
    node_t r3 = {{{NULL}}, "r3", 1, 0};

    h2o_http2_scheduler_init(&root);

    /* setup the proirity groups */
    h2o_http2_scheduler_open(&g1.ref, &root, 201, 0);
    h2o_http2_scheduler_open(&g2.ref, &root, 101, 0);
    h2o_http2_scheduler_open(&g3.ref, &root, 1, 0);
    h2o_http2_scheduler_open(&g4.ref, &g3.ref.node, 1, 0);
    h2o_http2_scheduler_open(&g5.ref, &g1.ref.node, 1, 0);

    /* open r1 and set serving */
    h2o_http2_scheduler_open(&r1.ref, &g5.ref.node, 22, 0);
    h2o_http2_scheduler_activate(&r1.ref);
    output[0] = '\0';
    max_cnt = 5;
    h2o_http2_scheduler_run(&root, iterate_cb, NULL);
    ok(strcmp(output, "r1,r1,r1,r1,r1") == 0);

    /* open r2,r3 and serve */
    h2o_http2_scheduler_open(&r2.ref, &g1.ref.node, 22, 0);
    h2o_http2_scheduler_activate(&r2.ref);
    h2o_http2_scheduler_open(&r3.ref, &g1.ref.node, 22, 0);
    h2o_http2_scheduler_activate(&r3.ref);
    output[0] = '\0';
    max_cnt = 5;
    h2o_http2_scheduler_run(&root, iterate_cb, NULL);
    ok(strcmp(output, "r2,r3,r2,r3,r2") == 0);

    /* eventually disactive r2,r3 */
    r2.still_is_active = 0;
    r3.still_is_active = 0;
    output[0] = '\0';
    max_cnt = 5;
    h2o_http2_scheduler_run(&root, iterate_cb, NULL);
    ok(strcmp(output, "r3,r2,r1,r1,r1") == 0);

    /* close r2,r3 */
    h2o_http2_scheduler_close(&r2.ref);
    h2o_http2_scheduler_close(&r3.ref);
    output[0] = '\0';
    max_cnt = 5;
    h2o_http2_scheduler_run(&root, iterate_cb, NULL);
    ok(strcmp(output, "r1,r1,r1,r1,r1") == 0);

    h2o_http2_scheduler_close(&r1.ref);

    h2o_http2_scheduler_close(&g1.ref);
    h2o_http2_scheduler_close(&g2.ref);
    h2o_http2_scheduler_close(&g3.ref);
    h2o_http2_scheduler_close(&g4.ref);
    h2o_http2_scheduler_close(&g5.ref);
    h2o_http2_scheduler_dispose(&root);
}