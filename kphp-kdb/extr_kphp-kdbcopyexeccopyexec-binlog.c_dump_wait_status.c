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

/* Variables and functions */
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int WTERMSIG (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  out ; 

void dump_wait_status (int status) {
  if (WIFEXITED(status)) {
    fprintf (out, "exit:%d", WEXITSTATUS(status));
  } else if (WIFSIGNALED(status)) {
    fprintf (out, "sig:%d", WTERMSIG(status));
  } else {
    fprintf (out, "%d", status);
  }
}