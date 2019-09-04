#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;
struct TYPE_9__ {int /*<<< orphan*/  certificate_check; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {TYPE_1__ proxy_opts; } ;
struct TYPE_12__ {TYPE_2__ fetch_opts; } ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_PROXY_AUTO ; 
 void* _orig_http_proxy ; 
 void* _orig_https_proxy ; 
 int _orig_proxies_need_reset ; 
 int /*<<< orphan*/  _remote_proxy_host ; 
 int /*<<< orphan*/  _remote_proxy_pass ; 
 char* _remote_proxy_scheme ; 
 int /*<<< orphan*/  _remote_proxy_user ; 
 void* cl_getenv (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_setenv (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 TYPE_4__ g_options ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_3__*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,char*,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  proxy_cert_cb ; 

void test_online_clone__proxy_credentials_in_environment(void)
{
	git_buf url = GIT_BUF_INIT;

	if (!_remote_proxy_host || !_remote_proxy_user || !_remote_proxy_pass)
		cl_skip();

	_orig_http_proxy = cl_getenv("HTTP_PROXY");
	_orig_https_proxy = cl_getenv("HTTPS_PROXY");
	_orig_proxies_need_reset = 1;

	g_options.fetch_opts.proxy_opts.type = GIT_PROXY_AUTO;
	g_options.fetch_opts.proxy_opts.certificate_check = proxy_cert_cb;

	cl_git_pass(git_buf_printf(&url, "%s://%s:%s@%s/",
		_remote_proxy_scheme ? _remote_proxy_scheme : "http",
		_remote_proxy_user, _remote_proxy_pass, _remote_proxy_host));

	cl_setenv("HTTP_PROXY", url.ptr);
	cl_setenv("HTTPS_PROXY", url.ptr);

	cl_git_pass(git_clone(&g_repo, "http://github.com/libgit2/TestGitRepository", "./foo", &g_options));

	git_buf_dispose(&url);
}