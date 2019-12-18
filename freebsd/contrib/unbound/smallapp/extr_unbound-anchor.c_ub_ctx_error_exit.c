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
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  ub_ctx_delete (struct ub_ctx*) ; 
 scalar_t__ verb ; 

__attribute__((used)) static void
ub_ctx_error_exit(struct ub_ctx* ctx, const char* str, const char* str2)
{
	ub_ctx_delete(ctx);
	if(str && str2 && verb) printf("%s: %s\n", str, str2);
	if(verb) printf("error: could not create unbound resolver context\n");
	exit(0);
}