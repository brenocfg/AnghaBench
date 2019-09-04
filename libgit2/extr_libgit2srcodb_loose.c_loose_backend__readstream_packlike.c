#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ obj_hdr ;
struct TYPE_7__ {unsigned char* data; size_t len; } ;
struct TYPE_9__ {int /*<<< orphan*/  zstream; TYPE_1__ map; } ;
typedef  TYPE_3__ loose_readstream ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_ODB ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_object_typeisloose (int /*<<< orphan*/ ) ; 
 int git_zstream_set_input (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int parse_header_packlike (TYPE_2__*,size_t*,unsigned char const*,size_t) ; 

__attribute__((used)) static int loose_backend__readstream_packlike(
	obj_hdr *hdr,
	loose_readstream *stream)
{
	const unsigned char *data;
	size_t data_len, head_len;
	int error;

	data = stream->map.data;
	data_len = stream->map.len;

	/*
	 * read the object header, which is an (uncompressed)
	 * binary encoding of the object type and size.
	 */
	if ((error = parse_header_packlike(hdr, &head_len, data, data_len)) < 0)
		return error;

	if (!git_object_typeisloose(hdr->type)) {
		git_error_set(GIT_ERROR_ODB, "failed to inflate loose object");
		return -1;
	}

	return git_zstream_set_input(&stream->zstream,
		data + head_len, data_len - head_len);
}