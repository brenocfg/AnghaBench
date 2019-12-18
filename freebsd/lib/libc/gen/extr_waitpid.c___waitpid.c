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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 size_t INTERPOS_wait4 ; 
 scalar_t__* __libc_interposing ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*,int,struct rusage*) ; 

pid_t
__waitpid(pid_t pid, int *istat, int options)
{

	return (((pid_t (*)(pid_t, int *, int, struct rusage *))
	    __libc_interposing[INTERPOS_wait4])(pid, istat, options, NULL));
}