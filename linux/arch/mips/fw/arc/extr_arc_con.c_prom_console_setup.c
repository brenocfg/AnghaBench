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
struct console {int dummy; } ;

/* Variables and functions */
 int PROM_FLAG_USE_AS_CONSOLE ; 
 int prom_flags ; 

__attribute__((used)) static int prom_console_setup(struct console *co, char *options)
{
	return !(prom_flags & PROM_FLAG_USE_AS_CONSOLE);
}