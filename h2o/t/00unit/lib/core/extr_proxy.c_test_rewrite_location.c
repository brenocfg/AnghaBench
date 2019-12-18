#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_url_t ;
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_URL_SCHEME_HTTPS ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_init_pool (int /*<<< orphan*/ *) ; 
 int h2o_memis (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_url_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int) ; 
 TYPE_1__ rewrite_location (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_rewrite_location(void)
{
    h2o_url_t upstream;
    h2o_mem_pool_t pool;
    h2o_iovec_t ret;

    h2o_url_parse(H2O_STRLIT("http://realhost:81/real/"), &upstream);

    h2o_mem_init_pool(&pool);

    ret = rewrite_location(&pool, H2O_STRLIT("http://realhost:81/real/abc"), &upstream, &H2O_URL_SCHEME_HTTPS,
                           h2o_iovec_init(H2O_STRLIT("vhost:8443")), h2o_iovec_init(H2O_STRLIT("/virtual/")));
    ok(h2o_memis(ret.base, ret.len, H2O_STRLIT("https://vhost:8443/virtual/abc")));
    ret = rewrite_location(&pool, H2O_STRLIT("http://realhost:81/other/abc"), &upstream, &H2O_URL_SCHEME_HTTPS,
                           h2o_iovec_init(H2O_STRLIT("vhost:8443")), h2o_iovec_init(H2O_STRLIT("/virtual/")));
    ok(ret.base == NULL);
    ok(ret.len == 0);

    h2o_mem_clear_pool(&pool);
}