#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  type; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ obj_hdr ;
struct TYPE_13__ {int /*<<< orphan*/  data; int /*<<< orphan*/  type; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ git_rawobj ;
struct TYPE_14__ {size_t size; scalar_t__ ptr; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 scalar_t__ GIT_ADD_SIZET_OVERFLOW (size_t*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_ODB ; 
 int /*<<< orphan*/  git_buf_detach (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 scalar_t__ git_buf_init (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_object_typeisloose (int /*<<< orphan*/ ) ; 
 int git_zstream_inflatebuf (TYPE_3__*,unsigned char const*,size_t) ; 
 int parse_header_packlike (TYPE_1__*,size_t*,unsigned char const*,size_t) ; 

__attribute__((used)) static int read_loose_packlike(git_rawobj *out, git_buf *obj)
{
	git_buf body = GIT_BUF_INIT;
	const unsigned char *obj_data;
	obj_hdr hdr;
	size_t obj_len, head_len, alloc_size;
	int error;

	obj_data = (unsigned char *)obj->ptr;
	obj_len = obj->size;

	/*
	 * read the object header, which is an (uncompressed)
	 * binary encoding of the object type and size.
	 */
	if ((error = parse_header_packlike(&hdr, &head_len, obj_data, obj_len)) < 0)
		goto done;

	if (!git_object_typeisloose(hdr.type) || head_len > obj_len) {
		git_error_set(GIT_ERROR_ODB, "failed to inflate loose object");
		error = -1;
		goto done;
	}

	obj_data += head_len;
	obj_len -= head_len;

	/*
	 * allocate a buffer and inflate the data into it
	 */
	if (GIT_ADD_SIZET_OVERFLOW(&alloc_size, hdr.size, 1) ||
		git_buf_init(&body, alloc_size) < 0) {
		error = -1;
		goto done;
	}

	if ((error = git_zstream_inflatebuf(&body, obj_data, obj_len)) < 0)
		goto done;

	out->len = hdr.size;
	out->type = hdr.type;
	out->data = git_buf_detach(&body);

done:
	git_buf_dispose(&body);
	return error;
}