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
struct section_addr_info {int dummy; } ;
struct objfile {int dummy; } ;

/* Variables and functions */
 struct objfile* symbol_file_add_with_addrs_or_offsets (char*,int,struct section_addr_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

struct objfile *
symbol_file_add (char *name, int from_tty, struct section_addr_info *addrs,
		 int mainline, int flags)
{
  return symbol_file_add_with_addrs_or_offsets (name, from_tty, addrs, 0, 0, 
                                                mainline, flags);
}