#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int isoLevel; } ;
typedef  TYPE_1__ iso9660_disk ;
typedef  int (* cd9660_filename_conversion_functor ) (TYPE_1__*,char const*,char*,int) ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int cd9660_level1_convert_filename (TYPE_1__*,char const*,char*,int) ; 
 int cd9660_level2_convert_filename (TYPE_1__*,char const*,char*,int) ; 
 int stub1 (TYPE_1__*,char const*,char*,int) ; 

__attribute__((used)) static int
cd9660_convert_filename(iso9660_disk *diskStructure, const char *oldname,
    char *newname, int is_file)
{
	assert(1 <= diskStructure->isoLevel && diskStructure->isoLevel <= 2);
	/* NEW */
	cd9660_filename_conversion_functor conversion_function = NULL;
	if (diskStructure->isoLevel == 1)
		conversion_function = &cd9660_level1_convert_filename;
	else if (diskStructure->isoLevel == 2)
		conversion_function = &cd9660_level2_convert_filename;
	return (*conversion_function)(diskStructure, oldname, newname, is_file);
}