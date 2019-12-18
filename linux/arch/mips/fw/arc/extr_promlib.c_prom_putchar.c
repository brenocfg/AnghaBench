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
typedef  int /*<<< orphan*/  ULONG ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ArcWrite (int,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bc_disable () ; 
 int /*<<< orphan*/  bc_enable () ; 

void prom_putchar(char c)
{
	ULONG cnt;
	CHAR it = c;

	bc_disable();
	ArcWrite(1, &it, 1, &cnt);
	bc_enable();
}