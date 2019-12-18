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
 int SIGEMT ; 
 int SIGTRAP ; 
#define  T_BREAKPOINT 128 

int
gdb_cpu_signal(int type, int code)
{

	switch (type) {
	case T_BREAKPOINT: return (SIGTRAP);
	}
	return (SIGEMT);
}