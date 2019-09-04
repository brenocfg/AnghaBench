#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; } ;
struct TYPE_7__ {TYPE_1__ keys; } ;
typedef  TYPE_2__ h2o_http2_casper_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 TYPE_2__* h2o_http2_casper_create (int,int) ; 
 int /*<<< orphan*/  h2o_http2_casper_destroy (TYPE_2__*) ; 
 int h2o_http2_casper_lookup (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_lookup(void)
{
    h2o_http2_casper_t *casper;
    casper = h2o_http2_casper_create(13, 6);

    ok(h2o_http2_casper_lookup(casper, H2O_STRLIT("/index.html"), 0) == 0);
    ok(h2o_http2_casper_lookup(casper, H2O_STRLIT("/index.html"), 1) == 0);
    ok(casper->keys.size == 1);
    ok(h2o_http2_casper_lookup(casper, H2O_STRLIT("/index.html"), 0) == 1);
    ok(h2o_http2_casper_lookup(casper, H2O_STRLIT("/index.html"), 1) == 1);
    ok(casper->keys.size == 1);

    h2o_http2_casper_destroy(casper);
}