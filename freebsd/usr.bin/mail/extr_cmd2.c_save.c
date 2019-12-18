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
 int save1 (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saveignore ; 

int
save(void *v)
{
	char *str = v;

	return (save1(str, 1, "save", saveignore));
}