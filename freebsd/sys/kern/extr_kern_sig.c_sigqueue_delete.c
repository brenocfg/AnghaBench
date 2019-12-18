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
typedef  int /*<<< orphan*/  sigqueue_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGADDSET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SIGEMPTYSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigqueue_delete_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
sigqueue_delete(sigqueue_t *sq, int signo)
{
	sigset_t set;

	SIGEMPTYSET(set);
	SIGADDSET(set, signo);
	sigqueue_delete_set(sq, &set);
}