#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_http2_casper_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  get_end_of_cookie_value (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  h2o_http2_casper_consume_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * h2o_http2_casper_create (int,int) ; 
 int /*<<< orphan*/  h2o_http2_casper_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__ h2o_http2_casper_get_cookie (int /*<<< orphan*/ *) ; 
 int h2o_http2_casper_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ h2o_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_cookie(void)
{
    h2o_http2_casper_t *casper;

    casper = h2o_http2_casper_create(13, 6);

    h2o_iovec_t cookie = h2o_http2_casper_get_cookie(casper);
    ok(cookie.base == NULL);
    ok(cookie.len == 0);

    h2o_http2_casper_lookup(casper, H2O_STRLIT("/index.html"), 1);
    cookie = h2o_http2_casper_get_cookie(casper);
    ok(cookie.len != 0);
    cookie = h2o_strdup(NULL, cookie.base, cookie.len);
    h2o_http2_casper_destroy(casper);
    casper = h2o_http2_casper_create(13, 6);

    h2o_http2_casper_consume_cookie(casper, cookie.base, get_end_of_cookie_value(cookie.base, cookie.len));
    ok(h2o_http2_casper_lookup(casper, H2O_STRLIT("/index.html"), 0) == 1);
    ok(h2o_http2_casper_lookup(casper, H2O_STRLIT("/index.php"), 0) == 0);
    h2o_http2_casper_lookup(casper, H2O_STRLIT("/index.php"), 1);

    h2o_http2_casper_lookup(casper, H2O_STRLIT("/index.html"), 1);
    cookie = h2o_http2_casper_get_cookie(casper);
    ok(cookie.len != 0);
    cookie = h2o_strdup(NULL, cookie.base, cookie.len);

    h2o_http2_casper_destroy(casper);
    casper = h2o_http2_casper_create(13, 6);

    h2o_http2_casper_consume_cookie(casper, cookie.base, get_end_of_cookie_value(cookie.base, cookie.len));
    ok(h2o_http2_casper_lookup(casper, H2O_STRLIT("/index.html"), 0) == 1);
    ok(h2o_http2_casper_lookup(casper, H2O_STRLIT("/index.php"), 0) == 1);

    h2o_http2_casper_destroy(casper);
}