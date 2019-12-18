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
 int /*<<< orphan*/  puts_filtered (char*) ; 
 char* source_path ; 

__attribute__((used)) static void
show_directories (char *ignore, int from_tty)
{
  puts_filtered ("Source directories searched: ");
  puts_filtered (source_path);
  puts_filtered ("\n");
}