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
 int /*<<< orphan*/  howmany (int,int) ; 
 int /*<<< orphan*/  wbytes ; 
 int width ; 

__attribute__((used)) static void
set_width(int w)
{
	if (w <= 0 || w > VFNT_MAXDIMENSION)
		errx(1, "invalid width %d", w);
	width = w;
	wbytes = howmany(width, 8);
}