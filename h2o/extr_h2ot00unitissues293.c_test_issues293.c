#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_globalconf_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_URL_SCHEME_HTTP ; 
 int /*<<< orphan*/  H2O_URL_SCHEME_HTTPS ; 
 int /*<<< orphan*/  check (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  h2o_config_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_config_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_context_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_context_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_authority (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_loop ; 

void test_issues293()
{
    h2o_globalconf_t globalconf;

    h2o_config_init(&globalconf);

    /* register two hosts, using 80 and 443 */
    register_authority(&globalconf, h2o_iovec_init(H2O_STRLIT("default")), 65535);
    register_authority(&globalconf, h2o_iovec_init(H2O_STRLIT("host1")), 80);
    register_authority(&globalconf, h2o_iovec_init(H2O_STRLIT("host1")), 443);
    register_authority(&globalconf, h2o_iovec_init(H2O_STRLIT("host2")), 80);
    register_authority(&globalconf, h2o_iovec_init(H2O_STRLIT("host2")), 443);
    register_authority(&globalconf, h2o_iovec_init(H2O_STRLIT("host3")), 65535);

    h2o_context_init(&ctx, test_loop, &globalconf);

    /* run the tests */
    check(&H2O_URL_SCHEME_HTTP, "host1", "host1:80");
    check(&H2O_URL_SCHEME_HTTPS, "host1", "host1:443");
    check(&H2O_URL_SCHEME_HTTP, "host2", "host2:80");
    check(&H2O_URL_SCHEME_HTTPS, "host2", "host2:443");

    /* supplied port number in the Host header must be preferred */
    check(&H2O_URL_SCHEME_HTTP, "host1:80", "host1:80");
    check(&H2O_URL_SCHEME_HTTP, "host1:443", "host1:443");
    check(&H2O_URL_SCHEME_HTTPS, "host1:80", "host1:80");
    check(&H2O_URL_SCHEME_HTTPS, "host1:443", "host1:443");
    check(&H2O_URL_SCHEME_HTTP, "host2:80", "host2:80");
    check(&H2O_URL_SCHEME_HTTP, "host2:443", "host2:443");
    check(&H2O_URL_SCHEME_HTTPS, "host2:80", "host2:80");
    check(&H2O_URL_SCHEME_HTTPS, "host2:443", "host2:443");

    /* host-level conf without default port */
    check(&H2O_URL_SCHEME_HTTP, "host3", "host3:65535");
    check(&H2O_URL_SCHEME_HTTPS, "host3", "host3:65535");
    check(&H2O_URL_SCHEME_HTTP, "host3", "host3:65535");
    check(&H2O_URL_SCHEME_HTTPS, "host3", "host3:65535");
    check(&H2O_URL_SCHEME_HTTP, "host3:80", "host3:65535");
    check(&H2O_URL_SCHEME_HTTPS, "host3:80", "default:65535");
    check(&H2O_URL_SCHEME_HTTP, "host3:443", "default:65535");
    check(&H2O_URL_SCHEME_HTTPS, "host3:443", "host3:65535");

    /* upper-case */
    check(&H2O_URL_SCHEME_HTTP, "HoST1", "host1:80");
    check(&H2O_URL_SCHEME_HTTP, "HoST1:80", "host1:80");
    check(&H2O_URL_SCHEME_HTTPS, "HoST1", "host1:443");
    check(&H2O_URL_SCHEME_HTTPS, "HoST1:443", "host1:443");

    h2o_context_dispose(&ctx);
    h2o_config_dispose(&globalconf);
}