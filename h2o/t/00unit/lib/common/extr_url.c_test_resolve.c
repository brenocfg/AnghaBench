#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_16__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_15__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_18__ {int _port; TYPE_3__ path; TYPE_2__ host; TYPE_1__ authority; int /*<<< orphan*/ * scheme; } ;
typedef  TYPE_4__ h2o_url_t ;
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
struct TYPE_19__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_5__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_URL_SCHEME_HTTP ; 
 int /*<<< orphan*/  H2O_URL_SCHEME_HTTPS ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_init_pool (int /*<<< orphan*/ *) ; 
 int h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int h2o_url_get_port (TYPE_4__*) ; 
 int h2o_url_parse (char*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int h2o_url_parse_relative (char*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_5__ h2o_url_resolve (int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*,TYPE_4__*) ; 
 TYPE_5__ h2o_url_stringify (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_resolve(void)
{
    h2o_mem_pool_t pool;
    h2o_url_t base, relative, resolved;
    h2o_iovec_t final;
    int ret;

    h2o_mem_init_pool(&pool);

    ret = h2o_url_parse("http://example.com/dir/index.html", SIZE_MAX, &base);
    ok(ret == 0);

    ret = h2o_url_parse_relative("../assets/jquery.js", SIZE_MAX, &relative);
    ok(ret == 0);
    final = h2o_url_resolve(&pool, &base, &relative, &resolved);
    ok(h2o_memis(final.base, final.len, H2O_STRLIT("http://example.com/assets/jquery.js")));
    ok(resolved.scheme == &H2O_URL_SCHEME_HTTP);
    ok(h2o_memis(resolved.authority.base, resolved.authority.len, H2O_STRLIT("example.com")));
    ok(h2o_memis(resolved.host.base, resolved.host.len, H2O_STRLIT("example.com")));
    ok(resolved._port == 65535);
    ok(h2o_url_get_port(&resolved) == 80);
    ok(h2o_memis(resolved.path.base, resolved.path.len, H2O_STRLIT("/assets/jquery.js")));

    ret = h2o_url_parse_relative("foo.html", SIZE_MAX, &relative);
    ok(ret == 0);
    final = h2o_url_resolve(&pool, &base, &relative, &resolved);
    ok(h2o_memis(final.base, final.len, H2O_STRLIT("http://example.com/dir/foo.html")));
    ok(resolved.scheme == &H2O_URL_SCHEME_HTTP);
    ok(h2o_memis(resolved.authority.base, resolved.authority.len, H2O_STRLIT("example.com")));
    ok(h2o_memis(resolved.host.base, resolved.host.len, H2O_STRLIT("example.com")));
    ok(resolved._port == 65535);
    ok(h2o_url_get_port(&resolved) == 80);
    ok(h2o_memis(resolved.path.base, resolved.path.len, H2O_STRLIT("/dir/foo.html")));

    ret = h2o_url_parse_relative("./bar.txt", SIZE_MAX, &relative);
    ok(ret == 0);
    final = h2o_url_resolve(&pool, &base, &relative, &resolved);
    ok(h2o_memis(final.base, final.len, H2O_STRLIT("http://example.com/dir/bar.txt")));
    ok(resolved.scheme == &H2O_URL_SCHEME_HTTP);
    ok(h2o_memis(resolved.authority.base, resolved.authority.len, H2O_STRLIT("example.com")));
    ok(h2o_memis(resolved.host.base, resolved.host.len, H2O_STRLIT("example.com")));
    ok(resolved._port == 65535);
    ok(h2o_url_get_port(&resolved) == 80);
    ok(h2o_memis(resolved.path.base, resolved.path.len, H2O_STRLIT("/dir/bar.txt")));

    ret = h2o_url_parse_relative("../../../traverse", SIZE_MAX, &relative);
    ok(ret == 0);
    final = h2o_url_resolve(&pool, &base, &relative, &resolved);
    ok(h2o_memis(final.base, final.len, H2O_STRLIT("http://example.com/traverse")));
    ok(resolved.scheme == &H2O_URL_SCHEME_HTTP);
    ok(h2o_memis(resolved.authority.base, resolved.authority.len, H2O_STRLIT("example.com")));
    ok(h2o_memis(resolved.host.base, resolved.host.len, H2O_STRLIT("example.com")));
    ok(resolved._port == 65535);
    ok(h2o_url_get_port(&resolved) == 80);
    ok(h2o_memis(resolved.path.base, resolved.path.len, H2O_STRLIT("/traverse")));

    ret = h2o_url_parse_relative("http:foo.html", SIZE_MAX, &relative);
    ok(ret == 0);
    final = h2o_url_resolve(&pool, &base, &relative, &resolved);
    ok(h2o_memis(final.base, final.len, H2O_STRLIT("http://example.com/dir/foo.html")));
    ok(resolved.scheme == &H2O_URL_SCHEME_HTTP);
    ok(h2o_memis(resolved.authority.base, resolved.authority.len, H2O_STRLIT("example.com")));
    ok(h2o_memis(resolved.host.base, resolved.host.len, H2O_STRLIT("example.com")));
    ok(resolved._port == 65535);
    ok(h2o_url_get_port(&resolved) == 80);
    ok(h2o_memis(resolved.path.base, resolved.path.len, H2O_STRLIT("/dir/foo.html")));

    ret = h2o_url_parse_relative("http:/icon.ico", SIZE_MAX, &relative);
    ok(ret == 0);
    final = h2o_url_resolve(&pool, &base, &relative, &resolved);
    ok(h2o_memis(final.base, final.len, H2O_STRLIT("http://example.com/icon.ico")));
    ok(resolved.scheme == &H2O_URL_SCHEME_HTTP);
    ok(h2o_memis(resolved.authority.base, resolved.authority.len, H2O_STRLIT("example.com")));
    ok(h2o_memis(resolved.host.base, resolved.host.len, H2O_STRLIT("example.com")));
    ok(resolved._port == 65535);
    ok(h2o_url_get_port(&resolved) == 80);
    ok(h2o_memis(resolved.path.base, resolved.path.len, H2O_STRLIT("/icon.ico")));

    ret = h2o_url_parse_relative("https:/icon.ico", SIZE_MAX, &relative);
    ok(ret == 0);
    final = h2o_url_resolve(&pool, &base, &relative, &resolved);
    ok(h2o_memis(final.base, final.len, H2O_STRLIT("https://example.com/icon.ico")));
    ok(resolved.scheme == &H2O_URL_SCHEME_HTTPS);
    ok(h2o_memis(resolved.authority.base, resolved.authority.len, H2O_STRLIT("example.com")));
    ok(h2o_memis(resolved.host.base, resolved.host.len, H2O_STRLIT("example.com")));
    ok(resolved._port == 65535);
    ok(h2o_url_get_port(&resolved) == 443);
    ok(h2o_memis(resolved.path.base, resolved.path.len, H2O_STRLIT("/icon.ico")));

    ret = h2o_url_parse_relative("//example.jp:81/icon.ico", SIZE_MAX, &relative);
    ok(ret == 0);
    final = h2o_url_resolve(&pool, &base, &relative, &resolved);
    ok(h2o_memis(final.base, final.len, H2O_STRLIT("http://example.jp:81/icon.ico")));
    ok(resolved.scheme == &H2O_URL_SCHEME_HTTP);
    ok(h2o_memis(resolved.authority.base, resolved.authority.len, H2O_STRLIT("example.jp:81")));
    ok(h2o_memis(resolved.host.base, resolved.host.len, H2O_STRLIT("example.jp")));
    ok(resolved._port == 81);
    ok(h2o_url_get_port(&resolved) == 81);
    ok(h2o_memis(resolved.path.base, resolved.path.len, H2O_STRLIT("/icon.ico")));

    final = h2o_url_stringify(&pool, &base);
    ok(h2o_memis(final.base, final.len, H2O_STRLIT("http://example.com/dir/index.html")));

    h2o_mem_clear_pool(&pool);
}