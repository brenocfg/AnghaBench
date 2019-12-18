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
struct TYPE_9__ {char* member_1; TYPE_4__ ref; TYPE_1__ member_0; } ;
typedef  TYPE_3__ node_t ;
typedef  int /*<<< orphan*/  h2o_http2_scheduler_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  dump_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_close (TYPE_4__*) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_open (TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_rebind (TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int) ; 
 char* output ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_reprioritize_exclusive ; 

__attribute__((used)) static void test_reprioritize(void)
{
    /* from 5.3.3 of HTTP-2 draft 16
     *    ?                ?                ?                 ?
     *    |               / \               |                 |
     *    A              D   A              D                 D
     *   / \            /   / \            / \                |
     *  B   C     ==>  F   B   C   ==>    F   A       OR      A
     *     / \                 |             / \             /|\
     *    D   E                E            B   C           B C F
     *    |                                     |             |
     *    F                                     E             E
     *               (intermediate)   (non-exclusive)    (exclusive)
     */
    h2o_http2_scheduler_node_t root;
    node_t a = {{{NULL}}, "A"};
    node_t b = {{{NULL}}, "B"};
    node_t c = {{{NULL}}, "C"};
    node_t d = {{{NULL}}, "D"};
    node_t e = {{{NULL}}, "E"};
    node_t f = {{{NULL}}, "F"};

    h2o_http2_scheduler_init(&root);
    h2o_http2_scheduler_open(&a.ref, &root, 6, 0);
    h2o_http2_scheduler_open(&b.ref, &a.ref.node, 5, 0);
    h2o_http2_scheduler_open(&c.ref, &a.ref.node, 4, 0);
    h2o_http2_scheduler_open(&d.ref, &c.ref.node, 3, 0);
    h2o_http2_scheduler_open(&e.ref, &c.ref.node, 2, 0);
    h2o_http2_scheduler_open(&f.ref, &d.ref.node, 1, 0);

    output[0] = '\0';
    dump_tree(&root);
    ok(strcmp(output, "(A6(B5C4(D3(F1)E2)))") == 0);

    h2o_http2_scheduler_rebind(&a.ref, &d.ref.node, 1, test_reprioritize_exclusive);
    output[0] = '\0';
    dump_tree(&root);
    if (!test_reprioritize_exclusive) {
        ok(strcmp(output, "(D3(F1A1(B5C4(E2))))") == 0);
    } else {
        ok(strcmp(output, "(D3(A1(B5C4(E2)F1)))") == 0);
    }

    h2o_http2_scheduler_close(&a.ref);
    h2o_http2_scheduler_close(&b.ref);
    h2o_http2_scheduler_close(&c.ref);
    h2o_http2_scheduler_close(&d.ref);
    h2o_http2_scheduler_close(&e.ref);
    h2o_http2_scheduler_close(&f.ref);
    h2o_http2_scheduler_dispose(&root);
}