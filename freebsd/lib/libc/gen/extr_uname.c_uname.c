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
struct utsname {int dummy; } ;

/* Variables and functions */
 int __xuname (int,struct utsname*) ; 

int
uname(struct utsname *name)
{
	return __xuname(32, name);
}