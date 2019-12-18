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
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  cred; TYPE_4__* auth_context; } ;
typedef  TYPE_1__ http_server ;
struct TYPE_11__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;
struct TYPE_12__ {int (* next_token ) (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_buf_printf (TYPE_2__*,char*,char const*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apply_credentials(
	git_buf *buf,
	http_server *server,
	const char *header_name)
{
	git_buf token = GIT_BUF_INIT;
	int error = 0;

	if (!server->auth_context)
		goto done;

	if ((error = server->auth_context->next_token(&token, server->auth_context, server->cred)) < 0)
		goto done;

	error = git_buf_printf(buf, "%s: %s\r\n", header_name, token.ptr);

done:
	git_buf_dispose(&token);
	return error;
}