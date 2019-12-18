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
struct parse_opt_ctx_t {int dummy; } ;
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct parse_opt_ctx_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_options_start_1 (struct parse_opt_ctx_t*,int,char const**,char const*,struct option const*,int) ; 

void parse_options_start(struct parse_opt_ctx_t *ctx,
			 int argc, const char **argv, const char *prefix,
			 const struct option *options, int flags)
{
	memset(ctx, 0, sizeof(*ctx));
	parse_options_start_1(ctx, argc, argv, prefix, options, flags);
}