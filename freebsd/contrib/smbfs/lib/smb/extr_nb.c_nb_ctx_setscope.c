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
struct nb_ctx {int /*<<< orphan*/ * nb_scope; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  nls_str_upper (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  smb_error (char*,int /*<<< orphan*/ ,char const*) ; 
 size_t strlen (char const*) ; 

int
nb_ctx_setscope(struct nb_ctx *ctx, const char *scope)
{
	size_t slen = strlen(scope);

	if (slen >= 128) {
		smb_error("scope '%s' is too long", 0, scope);
		return ENAMETOOLONG;
	}
	if (ctx->nb_scope)
		free(ctx->nb_scope);
	ctx->nb_scope = malloc(slen + 1);
	if (ctx->nb_scope == NULL)
		return ENOMEM;
	nls_str_upper(ctx->nb_scope, scope);
	return 0;
}