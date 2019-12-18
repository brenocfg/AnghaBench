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
 TYPE_1__ child_ops ; 
 int /*<<< orphan*/  fbsd_thread_active ; 
 int /*<<< orphan*/  fbsd_thread_ops ; 
 scalar_t__ fbsd_thread_present ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (char*,char*,char**) ; 

__attribute__((used)) static void
fbsd_thread_create_inferior (char *exec_file, char *allargs, char **env)
{
  if (fbsd_thread_present && !fbsd_thread_active)
    push_target(&fbsd_thread_ops);

  child_ops.to_create_inferior (exec_file, allargs, env);
}