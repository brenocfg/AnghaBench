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
struct parse_opt_ctx_t {char const** argv; int argc; } ;
struct option {int dummy; } ;
struct object_id {int dummy; } ;
typedef  enum parse_opt_result { ____Placeholder_parse_opt_result } parse_opt_result ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_ARG (char const*) ; 
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 scalar_t__ add_cacheinfo (unsigned int,struct object_id*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int error (char*) ; 
 scalar_t__ get_oid_hex (char const*,struct object_id*) ; 
 int /*<<< orphan*/  parse_new_style_cacheinfo (char const*,unsigned int*,struct object_id*,char const**) ; 
 scalar_t__ strtoul_ui (char const*,int,unsigned int*) ; 

__attribute__((used)) static enum parse_opt_result cacheinfo_callback(
	struct parse_opt_ctx_t *ctx, const struct option *opt,
	const char *arg, int unset)
{
	struct object_id oid;
	unsigned int mode;
	const char *path;

	BUG_ON_OPT_NEG(unset);
	BUG_ON_OPT_ARG(arg);

	if (!parse_new_style_cacheinfo(ctx->argv[1], &mode, &oid, &path)) {
		if (add_cacheinfo(mode, &oid, path, 0))
			die("git update-index: --cacheinfo cannot add %s", path);
		ctx->argv++;
		ctx->argc--;
		return 0;
	}
	if (ctx->argc <= 3)
		return error("option 'cacheinfo' expects <mode>,<sha1>,<path>");
	if (strtoul_ui(*++ctx->argv, 8, &mode) ||
	    get_oid_hex(*++ctx->argv, &oid) ||
	    add_cacheinfo(mode, &oid, *++ctx->argv, 0))
		die("git update-index: --cacheinfo cannot add %s", *ctx->argv);
	ctx->argc -= 3;
	return 0;
}