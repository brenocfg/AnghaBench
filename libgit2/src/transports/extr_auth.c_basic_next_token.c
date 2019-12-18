#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_http_auth_context ;
struct TYPE_13__ {int /*<<< orphan*/  password; int /*<<< orphan*/  username; } ;
typedef  TYPE_1__ git_cred_userpass_plaintext ;
struct TYPE_14__ {scalar_t__ credtype; } ;
typedef  TYPE_2__ git_cred ;
struct TYPE_15__ {scalar_t__ size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 scalar_t__ GIT_CREDTYPE_USERPASS_PLAINTEXT ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__memzero (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  git_buf_cstr (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 scalar_t__ git_buf_encode_base64 (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ git_buf_oom (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_buf_puts (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int basic_next_token(
	git_buf *out,
	git_http_auth_context *ctx,
	git_cred *c)
{
	git_cred_userpass_plaintext *cred;
	git_buf raw = GIT_BUF_INIT;
	int error = -1;

	GIT_UNUSED(ctx);

	if (c->credtype != GIT_CREDTYPE_USERPASS_PLAINTEXT) {
		git_error_set(GIT_ERROR_INVALID, "invalid credential type for basic auth");
		goto on_error;
	}

	cred = (git_cred_userpass_plaintext *)c;

	git_buf_printf(&raw, "%s:%s", cred->username, cred->password);

	if (git_buf_oom(&raw) ||
		git_buf_puts(out, "Basic ") < 0 ||
		git_buf_encode_base64(out, git_buf_cstr(&raw), raw.size) < 0)
		goto on_error;

	error = 0;

on_error:
	if (raw.size)
		git__memzero(raw.ptr, raw.size);

	git_buf_dispose(&raw);
	return error;
}