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
 int VFNT_MAXDIMENSION ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int height ; 

__attribute__((used)) static void
set_height(int h)
{
	if (h <= 0 || h > VFNT_MAXDIMENSION)
		errx(1, "invalid height %d", h);
	height = h;
}