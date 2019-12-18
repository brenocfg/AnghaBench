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
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {char* filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 TYPE_2__* cf ; 
 TYPE_1__* current_config_kvi ; 

const char *current_config_name(void)
{
	const char *name;
	if (current_config_kvi)
		name = current_config_kvi->filename;
	else if (cf)
		name = cf->name;
	else
		BUG("current_config_name called outside config callback");
	return name ? name : "";
}