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
struct ibv_context {int dummy; } ;

/* Variables and functions */
 char* getenv (char*) ; 

__attribute__((used)) static int rwq_sig_enabled(struct ibv_context *context)
{
	char *env;

	env = getenv("MLX5_RWQ_SIGNATURE");
	if (env)
		return 1;

	return 0;
}