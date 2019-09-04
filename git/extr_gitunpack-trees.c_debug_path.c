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
struct TYPE_2__ {char* path; } ;
struct traverse_info {TYPE_1__ name; struct traverse_info* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void debug_path(struct traverse_info *info)
{
	if (info->prev) {
		debug_path(info->prev);
		if (*info->prev->name.path)
			putchar('/');
	}
	printf("%s", info->name.path);
}