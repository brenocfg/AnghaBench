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
struct TYPE_4__ {int origin_type; } ;
struct TYPE_3__ {int origin_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
#define  CONFIG_ORIGIN_BLOB 132 
#define  CONFIG_ORIGIN_CMDLINE 131 
#define  CONFIG_ORIGIN_FILE 130 
#define  CONFIG_ORIGIN_STDIN 129 
#define  CONFIG_ORIGIN_SUBMODULE_BLOB 128 
 TYPE_2__* cf ; 
 TYPE_1__* current_config_kvi ; 

const char *current_config_origin_type(void)
{
	int type;
	if (current_config_kvi)
		type = current_config_kvi->origin_type;
	else if(cf)
		type = cf->origin_type;
	else
		BUG("current_config_origin_type called outside config callback");

	switch (type) {
	case CONFIG_ORIGIN_BLOB:
		return "blob";
	case CONFIG_ORIGIN_FILE:
		return "file";
	case CONFIG_ORIGIN_STDIN:
		return "standard input";
	case CONFIG_ORIGIN_SUBMODULE_BLOB:
		return "submodule-blob";
	case CONFIG_ORIGIN_CMDLINE:
		return "command line";
	default:
		BUG("unknown config origin type");
	}
}