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
struct target_ops {int /*<<< orphan*/  (* to_create_inferior ) (char*,char*,char**) ;} ;

/* Variables and functions */
 struct target_ops* find_default_run_target (char*) ; 
 int /*<<< orphan*/  stub1 (char*,char*,char**) ; 

void
find_default_create_inferior (char *exec_file, char *allargs, char **env)
{
  struct target_ops *t;

  t = find_default_run_target ("run");
  (t->to_create_inferior) (exec_file, allargs, env);
  return;
}