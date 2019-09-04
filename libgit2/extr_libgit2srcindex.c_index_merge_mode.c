#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int mode; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_6__ {scalar_t__ distrust_filemode; scalar_t__ no_symlinks; } ;
typedef  TYPE_2__ git_index ;

/* Variables and functions */
 scalar_t__ S_ISLNK (unsigned int) ; 
 scalar_t__ S_ISREG (unsigned int) ; 
 unsigned int git_index__create_mode (unsigned int) ; 

__attribute__((used)) static unsigned int index_merge_mode(
	git_index *index, git_index_entry *existing, unsigned int mode)
{
	if (index->no_symlinks && S_ISREG(mode) &&
		existing && S_ISLNK(existing->mode))
		return existing->mode;

	if (index->distrust_filemode && S_ISREG(mode))
		return (existing && S_ISREG(existing->mode)) ?
			existing->mode : git_index__create_mode(0666);

	return git_index__create_mode(mode);
}