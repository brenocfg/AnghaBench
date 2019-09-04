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
typedef  int mode_t ;
struct TYPE_3__ {scalar_t__ mode; } ;
typedef  TYPE_1__ git_repository_init_options ;

/* Variables and functions */
 scalar_t__ GIT_REPOSITORY_INIT_SHARED_ALL ; 
 scalar_t__ GIT_REPOSITORY_INIT_SHARED_GROUP ; 
 scalar_t__ GIT_REPOSITORY_INIT_SHARED_UMASK ; 
 int S_ISGID ; 

__attribute__((used)) static mode_t pick_dir_mode(git_repository_init_options *opts)
{
	if (opts->mode == GIT_REPOSITORY_INIT_SHARED_UMASK)
		return 0777;
	if (opts->mode == GIT_REPOSITORY_INIT_SHARED_GROUP)
		return (0775 | S_ISGID);
	if (opts->mode == GIT_REPOSITORY_INIT_SHARED_ALL)
		return (0777 | S_ISGID);
	return opts->mode;
}