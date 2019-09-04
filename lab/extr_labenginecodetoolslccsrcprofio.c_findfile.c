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
struct file {char* name; struct file* link; } ;

/* Variables and functions */
 struct file* filelist ; 

__attribute__((used)) static struct file *findfile(char *name) {
	struct file *p;

	for (p = filelist; p; p = p->link)
		if (p->name == name)
			return p;
	return 0;
}