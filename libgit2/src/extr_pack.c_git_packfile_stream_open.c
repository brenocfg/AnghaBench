#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct git_pack_file {int dummy; } ;
struct TYPE_6__ {void* next_out; void* next_in; int /*<<< orphan*/  zfree; int /*<<< orphan*/  zalloc; } ;
struct TYPE_5__ {TYPE_3__ zstream; struct git_pack_file* p; int /*<<< orphan*/  curpos; } ;
typedef  TYPE_1__ git_packfile_stream ;
typedef  int /*<<< orphan*/  git_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_ZLIB ; 
 void* Z_NULL ; 
 int Z_OK ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int inflateInit (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  use_git_alloc ; 
 int /*<<< orphan*/  use_git_free ; 

int git_packfile_stream_open(git_packfile_stream *obj, struct git_pack_file *p, git_off_t curpos)
{
	int st;

	memset(obj, 0, sizeof(git_packfile_stream));
	obj->curpos = curpos;
	obj->p = p;
	obj->zstream.zalloc = use_git_alloc;
	obj->zstream.zfree = use_git_free;
	obj->zstream.next_in = Z_NULL;
	obj->zstream.next_out = Z_NULL;
	st = inflateInit(&obj->zstream);
	if (st != Z_OK) {
		git_error_set(GIT_ERROR_ZLIB, "failed to init packfile stream");
		return -1;
	}

	return 0;
}