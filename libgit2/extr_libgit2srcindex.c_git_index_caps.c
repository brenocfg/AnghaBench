#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ no_symlinks; scalar_t__ distrust_filemode; scalar_t__ ignore_case; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int GIT_INDEX_CAPABILITY_IGNORE_CASE ; 
 int GIT_INDEX_CAPABILITY_NO_FILEMODE ; 
 int GIT_INDEX_CAPABILITY_NO_SYMLINKS ; 

int git_index_caps(const git_index *index)
{
	return ((index->ignore_case ? GIT_INDEX_CAPABILITY_IGNORE_CASE : 0) |
			(index->distrust_filemode ? GIT_INDEX_CAPABILITY_NO_FILEMODE : 0) |
			(index->no_symlinks ? GIT_INDEX_CAPABILITY_NO_SYMLINKS : 0));
}