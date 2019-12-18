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
typedef  enum linux_mountops { ____Placeholder_linux_mountops } linux_mountops ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_CALL2 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mount ; 

LONG
ArcMount(char *name, enum linux_mountops op)
{
	return ARC_CALL2(mount, name, op);
}