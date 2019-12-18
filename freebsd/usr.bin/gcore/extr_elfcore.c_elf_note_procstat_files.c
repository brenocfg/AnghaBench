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
struct kinfo_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_PROC_FILEDESC ; 
 void* procstat_sysctl (void*,int /*<<< orphan*/ ,int,size_t*) ; 

__attribute__((used)) static void *
elf_note_procstat_files(void *arg, size_t *sizep)
{

	return (procstat_sysctl(arg, KERN_PROC_FILEDESC,
	    sizeof(struct kinfo_file), sizep));
}