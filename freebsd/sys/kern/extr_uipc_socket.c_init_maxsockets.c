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
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imax (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maxfiles ; 
 int /*<<< orphan*/  maxsockets ; 

__attribute__((used)) static void
init_maxsockets(void *ignored)
{

	TUNABLE_INT_FETCH("kern.ipc.maxsockets", &maxsockets);
	maxsockets = imax(maxsockets, maxfiles);
}