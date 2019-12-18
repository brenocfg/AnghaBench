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
struct bitset {int dummy; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUSETBUFSIZ ; 
 int /*<<< orphan*/  CPU_SETSIZE ; 
 int /*<<< orphan*/  bitset_strprint (char*,int /*<<< orphan*/ ,struct bitset const*,int /*<<< orphan*/ ) ; 

char *
cpusetobj_strprint(char *buf, const cpuset_t *set)
{

	bitset_strprint(buf, CPUSETBUFSIZ, (const struct bitset *)set,
	    CPU_SETSIZE);
	return (buf);
}