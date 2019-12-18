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

/* Variables and functions */
 int /*<<< orphan*/  _orig_http_proxy ; 
 int /*<<< orphan*/  _orig_https_proxy ; 
 scalar_t__ _orig_proxies_need_reset ; 
 int /*<<< orphan*/  _remote_pass ; 
 int /*<<< orphan*/  _remote_proxy_host ; 
 int /*<<< orphan*/  _remote_proxy_pass ; 
 int /*<<< orphan*/  _remote_proxy_scheme ; 
 int /*<<< orphan*/  _remote_proxy_selfsigned ; 
 int /*<<< orphan*/  _remote_proxy_user ; 
 int /*<<< orphan*/  _remote_ssh_fingerprint ; 
 int /*<<< orphan*/  _remote_ssh_passphrase ; 
 int /*<<< orphan*/  _remote_ssh_privkey ; 
 int /*<<< orphan*/  _remote_ssh_pubkey ; 
 int /*<<< orphan*/  _remote_sslnoverify ; 
 int /*<<< orphan*/  _remote_url ; 
 int /*<<< orphan*/  _remote_user ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_setenv (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 

void test_online_clone__cleanup(void)
{
	if (g_repo) {
		git_repository_free(g_repo);
		g_repo = NULL;
	}
	cl_fixture_cleanup("./foo");

	git__free(_remote_url);
	git__free(_remote_user);
	git__free(_remote_pass);
	git__free(_remote_sslnoverify);
	git__free(_remote_ssh_pubkey);
	git__free(_remote_ssh_privkey);
	git__free(_remote_ssh_passphrase);
	git__free(_remote_ssh_fingerprint);
	git__free(_remote_proxy_scheme);
	git__free(_remote_proxy_host);
	git__free(_remote_proxy_user);
	git__free(_remote_proxy_pass);
	git__free(_remote_proxy_selfsigned);

	if (_orig_proxies_need_reset) {
		cl_setenv("HTTP_PROXY", _orig_http_proxy);
		cl_setenv("HTTPS_PROXY", _orig_https_proxy);

		git__free(_orig_http_proxy);
		git__free(_orig_https_proxy);
	}
}