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
typedef  enum parse_opt_result { ____Placeholder_parse_opt_result } parse_opt_result ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_ARG (char const*) ; 
 int PARSE_OPT_UNKNOWN ; 

enum parse_opt_result parse_opt_unknown_cb(struct parse_opt_ctx_t *ctx,
					   const struct option *opt,
					   const char *arg, int unset)
{
	BUG_ON_OPT_ARG(arg);
	return PARSE_OPT_UNKNOWN;
}