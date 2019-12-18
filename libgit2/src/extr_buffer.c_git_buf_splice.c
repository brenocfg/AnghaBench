#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t size; char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  ENSURE_SIZE (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 

int git_buf_splice(
	git_buf *buf,
	size_t where,
	size_t nb_to_remove,
	const char *data,
	size_t nb_to_insert)
{
	char *splice_loc;
	size_t new_size, alloc_size;

	assert(buf && where <= buf->size && nb_to_remove <= buf->size - where);

	splice_loc = buf->ptr + where;

	/* Ported from git.git
	 * https://github.com/git/git/blob/16eed7c/strbuf.c#L159-176
	 */
	GIT_ERROR_CHECK_ALLOC_ADD(&new_size, (buf->size - nb_to_remove), nb_to_insert);
	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_size, new_size, 1);
	ENSURE_SIZE(buf, alloc_size);

	memmove(splice_loc + nb_to_insert,
		splice_loc + nb_to_remove,
		buf->size - where - nb_to_remove);

	memcpy(splice_loc, data, nb_to_insert);

	buf->size = new_size;
	buf->ptr[buf->size] = '\0';
	return 0;
}