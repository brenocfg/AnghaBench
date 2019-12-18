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
struct ub_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  ub_ctx_delete (struct ub_ctx*) ; 
 int ub_ctx_set_option (struct ub_ctx*,char*,char const*) ; 
 char* ub_strerror (int) ; 
 scalar_t__ verb ; 

__attribute__((used)) static void
add_5011_probe_root(struct ub_ctx* ctx, const char* root_anchor_file)
{
	int r;
	r = ub_ctx_set_option(ctx, "auto-trust-anchor-file:", root_anchor_file);
	if(r) {
		if(verb) printf("add 5011 probe to ctx: %s\n", ub_strerror(r));
		ub_ctx_delete(ctx);
		exit(0);
	}
}