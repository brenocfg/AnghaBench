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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 scalar_t__ SIGISMEMBER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newnfs_sig_set ; 
 int nitems (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfs_sig_pending(sigset_t set)
{
	int i;
	
	for (i = 0 ; i < nitems(newnfs_sig_set); i++)
		if (SIGISMEMBER(set, newnfs_sig_set[i]))
			return (1);
	return (0);
}