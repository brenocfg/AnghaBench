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
struct unix_sockaddr_context {int /*<<< orphan*/  orig_dir; } ;

/* Variables and functions */
 scalar_t__ chdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unix_sockaddr_cleanup(struct unix_sockaddr_context *ctx)
{
	if (!ctx->orig_dir)
		return;
	/*
	 * If we fail, we can't just return an error, since we have
	 * moved the cwd of the whole process, which could confuse calling
	 * code.  We are better off to just die.
	 */
	if (chdir(ctx->orig_dir) < 0)
		die("unable to restore original working directory");
	free(ctx->orig_dir);
}