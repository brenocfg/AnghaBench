#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* string; } ;
struct TYPE_3__ {char const* string; } ;

/* Variables and functions */
 TYPE_2__* com_basegame ; 
 TYPE_1__* fs_gamedirvar ; 

const char *FS_GetCurrentGameDir(void)
{
	if(fs_gamedirvar->string[0])
		return fs_gamedirvar->string;

	return com_basegame->string;
}