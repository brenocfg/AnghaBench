#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* hx509_revoke_ctx ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_9__ {int /*<<< orphan*/ * path; } ;
struct TYPE_7__ {size_t len; TYPE_3__* val; } ;
struct TYPE_8__ {TYPE_1__ ocsps; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HX509_UNSUPPORTED_OPERATION ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char const*) ; 
 int load_ocsp (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 void* realloc (TYPE_3__*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

int
hx509_revoke_add_ocsp(hx509_context context,
		      hx509_revoke_ctx ctx,
		      const char *path)
{
    void *data;
    int ret;
    size_t i;

    if (strncmp(path, "FILE:", 5) != 0) {
	hx509_set_error_string(context, 0, HX509_UNSUPPORTED_OPERATION,
			       "unsupport type in %s", path);
	return HX509_UNSUPPORTED_OPERATION;
    }

    path += 5;

    for (i = 0; i < ctx->ocsps.len; i++) {
	if (strcmp(ctx->ocsps.val[0].path, path) == 0)
	    return 0;
    }

    data = realloc(ctx->ocsps.val,
		   (ctx->ocsps.len + 1) * sizeof(ctx->ocsps.val[0]));
    if (data == NULL) {
	hx509_clear_error_string(context);
	return ENOMEM;
    }

    ctx->ocsps.val = data;

    memset(&ctx->ocsps.val[ctx->ocsps.len], 0,
	   sizeof(ctx->ocsps.val[0]));

    ctx->ocsps.val[ctx->ocsps.len].path = strdup(path);
    if (ctx->ocsps.val[ctx->ocsps.len].path == NULL) {
	hx509_clear_error_string(context);
	return ENOMEM;
    }

    ret = load_ocsp(context, &ctx->ocsps.val[ctx->ocsps.len]);
    if (ret) {
	free(ctx->ocsps.val[ctx->ocsps.len].path);
	return ret;
    }
    ctx->ocsps.len++;

    return ret;
}