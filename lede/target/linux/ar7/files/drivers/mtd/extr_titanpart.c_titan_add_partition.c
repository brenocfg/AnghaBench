#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; unsigned int offset; unsigned int size; int /*<<< orphan*/  mask_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_WRITEABLE ; 
 size_t part_count ; 
 scalar_t__ strcmp (char*,char*) ; 
 TYPE_1__* titan_parts ; 

__attribute__((used)) static void titan_add_partition(char * env_name, unsigned int flash_base, unsigned int flash_end)
{
		titan_parts[part_count].name = env_name;
		titan_parts[part_count].offset = flash_base;
		titan_parts[part_count].size = flash_end-flash_base;
		titan_parts[part_count].mask_flags = (strcmp(env_name, "bootloader")==0|| 
			strcmp(env_name, "boot_env")==0 ||
			strcmp(env_name, "full_image")==0 )?MTD_WRITEABLE:0;
		part_count++;

}