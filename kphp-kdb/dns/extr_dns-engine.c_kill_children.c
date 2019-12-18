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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kill (scalar_t__,int) ; 
 scalar_t__* pids ; 
 int workers ; 

__attribute__((used)) static void kill_children (int signal) {
  int i;
  assert (workers);
  for (i = 0; i < workers; i++) {
    if (pids[i]) {
      kill (pids[i], signal);
    }
  }
}