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
 int /*<<< orphan*/  cmd_id ; 
 scalar_t__ getpid () ; 
 scalar_t__ sigusr2_pid ; 

__attribute__((used)) static inline int interrupted_by_cancelled (void) {
  return !cmd_id && sigusr2_pid && sigusr2_pid == getpid ();
}