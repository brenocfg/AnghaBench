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
struct xml_ctx {char const* name; int len; int /*<<< orphan*/  (* userFunc ) (struct xml_ctx*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (struct xml_ctx*,int /*<<< orphan*/ ) ; 
 char const* xrealloc (char const*,int) ; 
 int /*<<< orphan*/  xsnprintf (char const*,int,char*,char const*) ; 

__attribute__((used)) static void
xml_start_tag(void *userData, const char *name, const char **atts)
{
	struct xml_ctx *ctx = (struct xml_ctx *)userData;
	const char *c = strchr(name, ':');
	int old_namelen, new_len;

	if (c == NULL)
		c = name;
	else
		c++;

	old_namelen = strlen(ctx->name);
	new_len = old_namelen + strlen(c) + 2;

	if (new_len > ctx->len) {
		ctx->name = xrealloc(ctx->name, new_len);
		ctx->len = new_len;
	}
	xsnprintf(ctx->name + old_namelen, ctx->len - old_namelen, ".%s", c);

	FREE_AND_NULL(ctx->cdata);

	ctx->userFunc(ctx, 0);
}