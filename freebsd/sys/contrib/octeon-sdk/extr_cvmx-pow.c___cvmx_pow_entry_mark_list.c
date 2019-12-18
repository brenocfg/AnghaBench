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
typedef  size_t uint8_t ;
typedef  size_t __cvmx_pow_list_types_t ;

/* Variables and functions */
 char** __cvmx_pow_list_names ; 
 int /*<<< orphan*/  printf (char*,int,char*,char*) ; 

__attribute__((used)) static int __cvmx_pow_entry_mark_list(int entry_num, __cvmx_pow_list_types_t entry_type, uint8_t entry_list[])
{
    if (entry_list[entry_num] == 0)
    {
        entry_list[entry_num] = entry_type;
        return 0;
    }
    else
    {
        printf("\nWARNING: Entry %d already on list %s, but we tried to add it to %s\n",
               entry_num, __cvmx_pow_list_names[entry_list[entry_num]], __cvmx_pow_list_names[entry_type]);
        return -1;
    }
}