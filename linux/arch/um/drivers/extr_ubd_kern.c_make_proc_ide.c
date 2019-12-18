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

/* Variables and functions */
 void* proc_ide ; 
 int /*<<< orphan*/ * proc_ide_root ; 
 void* proc_mkdir (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void make_proc_ide(void)
{
	proc_ide_root = proc_mkdir("ide", NULL);
	proc_ide = proc_mkdir("ide0", proc_ide_root);
}