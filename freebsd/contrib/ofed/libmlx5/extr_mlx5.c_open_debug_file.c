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
struct mlx5_context {void* dbg_fp; } ;

/* Variables and functions */
 void* fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (void*,char*,char*) ; 
 char* getenv (char*) ; 
 void* stderr ; 

__attribute__((used)) static void open_debug_file(struct mlx5_context *ctx)
{
	char *env;

	env = getenv("MLX5_DEBUG_FILE");
	if (!env) {
		ctx->dbg_fp = stderr;
		return;
	}

	ctx->dbg_fp = fopen(env, "aw+");
	if (!ctx->dbg_fp) {
		fprintf(stderr, "Failed opening debug file %s, using stderr\n", env);
		ctx->dbg_fp = stderr;
		return;
	}
}