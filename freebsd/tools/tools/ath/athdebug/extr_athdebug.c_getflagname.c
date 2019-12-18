#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_3__ {scalar_t__ bit; char const* name; } ;

/* Variables and functions */
 TYPE_1__* flags ; 
 int nitems (TYPE_1__*) ; 

__attribute__((used)) static const char *
getflagname(u_int flag)
{
	int i;

	for (i = 0; i < nitems(flags); i++)
		if (flags[i].bit == flag)
			return flags[i].name;
	return "???";
}