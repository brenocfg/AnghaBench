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
struct target_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf_filtered (char*,char*) ; 
 char* vmcore ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

__attribute__((used)) static void
kgdb_trgt_files_info(struct target_ops *target)
{

	printf_filtered ("\t`%s', ", vmcore);
	wrap_here ("        ");
	printf_filtered ("file type %s.\n", "FreeBSD kernel vmcore");
}