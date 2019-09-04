#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ pass; scalar_t__ user; } ;
struct TYPE_12__ {TYPE_4__* url_cred; TYPE_1__ url; TYPE_4__* cred; } ;
typedef  TYPE_2__ http_server ;
struct TYPE_13__ {int (* next_token ) (int /*<<< orphan*/ *,TYPE_3__*,char const*,TYPE_4__*) ;} ;
typedef  TYPE_3__ git_http_auth_context ;
struct TYPE_14__ {int /*<<< orphan*/  credtype; } ;
typedef  TYPE_4__ git_cred ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 scalar_t__ auth_context_match (TYPE_3__**,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  credtype_match ; 
 scalar_t__ git_cred_userpass_plaintext_new (TYPE_4__**,scalar_t__,scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ *,TYPE_3__*,char const*,TYPE_4__*) ; 

__attribute__((used)) static int apply_credentials(
	git_buf *buf,
	http_server *server,
	const char *header_name)
{
	git_cred *cred = server->cred;
	git_http_auth_context *context;

	/* Apply the credentials given to us in the URL */
	if (!cred && server->url.user && server->url.pass) {
		if (!server->url_cred &&
			git_cred_userpass_plaintext_new(&server->url_cred,
			    server->url.user, server->url.pass) < 0)
			return -1;

		cred = server->url_cred;
	}

	if (!cred)
		return 0;

	/* Get or create a context for the best scheme for this cred type */
	if (auth_context_match(&context, server,
	    credtype_match, &cred->credtype) < 0)
		return -1;

	if (!context)
		return 0;

	return context->next_token(buf, context, header_name, cred);
}