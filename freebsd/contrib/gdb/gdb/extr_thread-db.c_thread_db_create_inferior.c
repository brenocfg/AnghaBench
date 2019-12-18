#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* to_create_inferior ) (char*,char*,char**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  keep_thread_db ; 
 int /*<<< orphan*/  stub1 (char*,char*,char**) ; 
 TYPE_1__* target_beneath ; 
 int /*<<< orphan*/  thread_db_ops ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 
 scalar_t__ using_thread_db ; 

__attribute__((used)) static void
thread_db_create_inferior (char *exec_file, char *allargs, char **env)
{
  if (!keep_thread_db)
    {
      unpush_target (&thread_db_ops);
      using_thread_db = 0;
    }

  target_beneath->to_create_inferior (exec_file, allargs, env);
}