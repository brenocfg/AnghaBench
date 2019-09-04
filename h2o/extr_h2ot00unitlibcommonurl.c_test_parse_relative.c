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
typedef  int /*<<< orphan*/  parsed ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * base; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * base; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * base; } ;
struct TYPE_10__ {int _port; TYPE_3__ path; TYPE_2__ host; TYPE_1__ authority; int /*<<< orphan*/ * scheme; } ;
typedef  TYPE_4__ h2o_url_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_URL_SCHEME_HTTP ; 
 int /*<<< orphan*/  H2O_URL_SCHEME_HTTPS ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 int h2o_memis (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int h2o_url_parse_relative (char*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_parse_relative(void)
{
    h2o_url_t parsed;
    int ret;

    memset(&parsed, 0x55, sizeof(parsed));
    ret = h2o_url_parse_relative("abc", SIZE_MAX, &parsed);
    ok(ret == 0);
    ok(parsed.scheme == NULL);
    ok(parsed.authority.base == NULL);
    ok(parsed.host.base == NULL);
    ok(parsed._port == 65535);
    ok(h2o_memis(parsed.path.base, parsed.path.len, H2O_STRLIT("abc")));

    memset(&parsed, 0x55, sizeof(parsed));
    ret = h2o_url_parse_relative("/abc", SIZE_MAX, &parsed);
    ok(ret == 0);
    ok(parsed.scheme == NULL);
    ok(parsed.authority.base == NULL);
    ok(parsed.host.base == NULL);
    ok(parsed._port == 65535);
    ok(h2o_memis(parsed.path.base, parsed.path.len, H2O_STRLIT("/abc")));

    memset(&parsed, 0x55, sizeof(parsed));
    ret = h2o_url_parse_relative("http:abc", SIZE_MAX, &parsed);
    ok(ret == 0);
    ok(parsed.scheme == &H2O_URL_SCHEME_HTTP);
    ok(parsed.authority.base == NULL);
    ok(parsed.host.base == NULL);
    ok(parsed._port == 65535);
    ok(h2o_memis(parsed.path.base, parsed.path.len, H2O_STRLIT("abc")));

    memset(&parsed, 0x55, sizeof(parsed));
    ret = h2o_url_parse_relative("//host", SIZE_MAX, &parsed);
    ok(ret == 0);
    ok(parsed.scheme == NULL);
    ok(h2o_memis(parsed.authority.base, parsed.authority.len, H2O_STRLIT("host")));
    ok(h2o_memis(parsed.host.base, parsed.host.len, H2O_STRLIT("host")));
    ok(parsed._port == 65535);
    ok(h2o_memis(parsed.path.base, parsed.path.len, H2O_STRLIT("/")));

    memset(&parsed, 0x55, sizeof(parsed));
    ret = h2o_url_parse_relative("//host:12345/path", SIZE_MAX, &parsed);
    ok(ret == 0);
    ok(parsed.scheme == NULL);
    ok(h2o_memis(parsed.authority.base, parsed.authority.len, H2O_STRLIT("host:12345")));
    ok(h2o_memis(parsed.host.base, parsed.host.len, H2O_STRLIT("host")));
    ok(parsed._port == 12345);
    ok(h2o_memis(parsed.path.base, parsed.path.len, H2O_STRLIT("/path")));

    memset(&parsed, 0x55, sizeof(parsed));
    ret = h2o_url_parse_relative("https://host:12345/path", SIZE_MAX, &parsed);
    ok(ret == 0);
    ok(parsed.scheme == &H2O_URL_SCHEME_HTTPS);
    ok(h2o_memis(parsed.authority.base, parsed.authority.len, H2O_STRLIT("host:12345")));
    ok(h2o_memis(parsed.host.base, parsed.host.len, H2O_STRLIT("host")));
    ok(parsed._port == 12345);
    ok(h2o_memis(parsed.path.base, parsed.path.len, H2O_STRLIT("/path")));
}