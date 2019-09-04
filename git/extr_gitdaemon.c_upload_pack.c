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
struct child_process {int /*<<< orphan*/  env_array; int /*<<< orphan*/  args; } ;
struct argv_array {int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  argv_array_pushv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int run_service_command (struct child_process*) ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static int upload_pack(const struct argv_array *env)
{
	struct child_process cld = CHILD_PROCESS_INIT;
	argv_array_pushl(&cld.args, "upload-pack", "--strict", NULL);
	argv_array_pushf(&cld.args, "--timeout=%u", timeout);

	argv_array_pushv(&cld.env_array, env->argv);

	return run_service_command(&cld);
}