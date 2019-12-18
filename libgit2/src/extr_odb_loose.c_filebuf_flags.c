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
struct TYPE_3__ {int object_zlib_level; scalar_t__ fsync_object_files; } ;
typedef  TYPE_1__ loose_backend ;

/* Variables and functions */
 int GIT_FILEBUF_DEFLATE_SHIFT ; 
 int GIT_FILEBUF_FSYNC ; 
 int GIT_FILEBUF_TEMPORARY ; 
 scalar_t__ git_repository__fsync_gitdir ; 

__attribute__((used)) static int filebuf_flags(loose_backend *backend)
{
	int flags = GIT_FILEBUF_TEMPORARY |
		(backend->object_zlib_level << GIT_FILEBUF_DEFLATE_SHIFT);

	if (backend->fsync_object_files || git_repository__fsync_gitdir)
		flags |= GIT_FILEBUF_FSYNC;

	return flags;
}