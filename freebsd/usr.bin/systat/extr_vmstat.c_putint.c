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
 int /*<<< orphan*/  SI ; 
 int /*<<< orphan*/  do_putuint64 (int,int,int,int,int /*<<< orphan*/ ) ; 

void
putint(int n, int l, int lc, int w)
{

	do_putuint64(n, l, lc, w, SI);
}