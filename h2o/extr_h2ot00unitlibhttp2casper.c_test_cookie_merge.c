#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ h2o_iovec_t ;
struct TYPE_11__ {int size; } ;
struct TYPE_13__ {TYPE_1__ keys; } ;
typedef  TYPE_3__ h2o_http2_casper_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  get_end_of_cookie_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_http2_casper_consume_cookie (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* h2o_http2_casper_create (int,int) ; 
 int /*<<< orphan*/  h2o_http2_casper_destroy (TYPE_3__*) ; 
 TYPE_2__ h2o_http2_casper_get_cookie (TYPE_3__*) ; 
 int h2o_http2_casper_lookup (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ h2o_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_cookie_merge(void)
{
    h2o_http2_casper_t *casper;

    casper = h2o_http2_casper_create(13, 6);
    h2o_http2_casper_lookup(casper, H2O_STRLIT("/index.html"), 1);
    h2o_iovec_t cookie1 = h2o_http2_casper_get_cookie(casper);
    cookie1 = h2o_strdup(NULL, cookie1.base, cookie1.len);
    h2o_http2_casper_destroy(casper);

    casper = h2o_http2_casper_create(13, 6);
    h2o_http2_casper_lookup(casper, H2O_STRLIT("/index.php"), 1);
    h2o_iovec_t cookie2 = h2o_http2_casper_get_cookie(casper);
    cookie2 = h2o_strdup(NULL, cookie2.base, cookie2.len);
    h2o_http2_casper_destroy(casper);

    casper = h2o_http2_casper_create(13, 6);
    h2o_http2_casper_consume_cookie(casper, cookie1.base, get_end_of_cookie_value(cookie1.base, cookie1.len));
    h2o_http2_casper_consume_cookie(casper, cookie1.base, get_end_of_cookie_value(cookie1.base, cookie1.len));
    ok(casper->keys.size == 1);
    ok(h2o_http2_casper_lookup(casper, H2O_STRLIT("/index.html"), 0) == 1);
    h2o_http2_casper_consume_cookie(casper, cookie2.base, get_end_of_cookie_value(cookie2.base, cookie2.len));
    ok(casper->keys.size == 2);
    ok(h2o_http2_casper_lookup(casper, H2O_STRLIT("/index.html"), 0) == 1);
    ok(h2o_http2_casper_lookup(casper, H2O_STRLIT("/index.php"), 0) == 1);
    h2o_http2_casper_destroy(casper);
}