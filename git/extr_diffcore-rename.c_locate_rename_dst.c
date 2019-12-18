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
struct diff_rename_dst {int dummy; } ;
struct diff_filespec {int dummy; } ;

/* Variables and functions */
 int find_rename_dst (struct diff_filespec*) ; 
 struct diff_rename_dst* rename_dst ; 

__attribute__((used)) static struct diff_rename_dst *locate_rename_dst(struct diff_filespec *two)
{
	int ofs = find_rename_dst(two);
	return ofs < 0 ? NULL : &rename_dst[ofs];
}