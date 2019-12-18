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
 int /*<<< orphan*/  fail_dirtmp (int /*<<< orphan*/ ) ; 
 int fwrite (char*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mf ; 
 int /*<<< orphan*/  modefile ; 

__attribute__((used)) static void
putdirattrs(char *buf, size_t size)
{

	if (mf != NULL && fwrite(buf, size, 1, mf) != 1)
		fail_dirtmp(modefile);
}