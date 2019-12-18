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
struct in_addr {int dummy; } ;
struct libalias {struct in_addr targetAddress; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBALIAS_LOCK (struct libalias*) ; 
 int /*<<< orphan*/  LIBALIAS_UNLOCK (struct libalias*) ; 

void
LibAliasSetTarget(struct libalias *la, struct in_addr target_addr)
{

	LIBALIAS_LOCK(la);
	la->targetAddress = target_addr;
	LIBALIAS_UNLOCK(la);
}