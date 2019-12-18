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
struct api_info {unsigned long group; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct api_info*) ; 
 struct api_info* api_table ; 

__attribute__((used)) static struct api_info *__get_info(unsigned long group)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(api_table); i++) {
		if (api_table[i].group == group)
			return &api_table[i];
	}
	return NULL;
}