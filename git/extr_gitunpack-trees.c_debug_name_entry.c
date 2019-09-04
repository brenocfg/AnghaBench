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
struct name_entry {char* path; int mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int,char*) ; 

__attribute__((used)) static void debug_name_entry(int i, struct name_entry *n)
{
	printf("ent#%d %06o %s\n", i,
	       n->path ? n->mode : 0,
	       n->path ? n->path : "(missing)");
}