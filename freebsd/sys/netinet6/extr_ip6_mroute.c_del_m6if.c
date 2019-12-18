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
typedef  int /*<<< orphan*/  mifi_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIF6_LOCK () ; 
 int /*<<< orphan*/  MIF6_UNLOCK () ; 
 int del_m6if_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
del_m6if(mifi_t *mifip)
{
	int cc;

	MIF6_LOCK();
	cc = del_m6if_locked(mifip);
	MIF6_UNLOCK();

	return (cc);
}