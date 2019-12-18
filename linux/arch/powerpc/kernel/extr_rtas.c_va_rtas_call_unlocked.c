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
typedef  int /*<<< orphan*/  va_list ;
struct rtas_args {void** rets; void** args; void* nret; void* nargs; void* token; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pa (struct rtas_args*) ; 
 int /*<<< orphan*/  __u32 ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  enter_rtas (int /*<<< orphan*/ ) ; 
 int va_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
va_rtas_call_unlocked(struct rtas_args *args, int token, int nargs, int nret,
		      va_list list)
{
	int i;

	args->token = cpu_to_be32(token);
	args->nargs = cpu_to_be32(nargs);
	args->nret  = cpu_to_be32(nret);
	args->rets  = &(args->args[nargs]);

	for (i = 0; i < nargs; ++i)
		args->args[i] = cpu_to_be32(va_arg(list, __u32));

	for (i = 0; i < nret; ++i)
		args->rets[i] = 0;

	enter_rtas(__pa(args));
}