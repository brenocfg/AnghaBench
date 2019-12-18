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
 int /*<<< orphan*/  printf_filtered (char*) ; 
 int /*<<< orphan*/  remote_open (char*,int) ; 

void
push_remote_target (char *name, int from_tty)
{
  printf_filtered ("Switching to remote protocol\n");
  remote_open (name, from_tty);
}