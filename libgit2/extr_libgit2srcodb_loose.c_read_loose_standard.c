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
struct TYPE_5__ {size_t size; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ obj_hdr ;
typedef  int /*<<< orphan*/  head ;
typedef  int /*<<< orphan*/  git_zstream ;
struct TYPE_6__ {unsigned char* data; size_t len; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ git_rawobj ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 scalar_t__ GIT_ADD_SIZET_OVERFLOW (size_t*,size_t,int) ; 
 int /*<<< orphan*/  GIT_ERROR_ODB ; 
 int /*<<< orphan*/  GIT_ERROR_ZLIB ; 
 int /*<<< orphan*/  GIT_ZSTREAM_INFLATE ; 
 int /*<<< orphan*/  GIT_ZSTREAM_INIT ; 
 int MAX_HEADER_LEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git__free (unsigned char*) ; 
 unsigned char* git__malloc (size_t) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_object_typeisloose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_zstream_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_zstream_free (int /*<<< orphan*/ *) ; 
 int git_zstream_get_output (unsigned char*,size_t*,int /*<<< orphan*/ *) ; 
 int git_zstream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_zstream_set_input (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int parse_header (TYPE_1__*,size_t*,unsigned char*,size_t) ; 

__attribute__((used)) static int read_loose_standard(git_rawobj *out, git_buf *obj)
{
	git_zstream zstream = GIT_ZSTREAM_INIT;
	unsigned char head[MAX_HEADER_LEN], *body = NULL;
	size_t decompressed, head_len, body_len, alloc_size;
	obj_hdr hdr;
	int error;

	if ((error = git_zstream_init(&zstream, GIT_ZSTREAM_INFLATE)) < 0 ||
		(error = git_zstream_set_input(&zstream, git_buf_cstr(obj), git_buf_len(obj))) < 0)
		goto done;

	decompressed = sizeof(head);

	/*
	 * inflate the initial part of the compressed buffer in order to
	 * parse the header; read the largest header possible, then push the
	 * remainder into the body buffer.
	 */
	if ((error = git_zstream_get_output(head, &decompressed, &zstream)) < 0 ||
		(error = parse_header(&hdr, &head_len, head, decompressed)) < 0)
		goto done;

	if (!git_object_typeisloose(hdr.type)) {
		git_error_set(GIT_ERROR_ODB, "failed to inflate disk object");
		error = -1;
		goto done;
	}

	/*
	 * allocate a buffer and inflate the object data into it
	 * (including the initial sequence in the head buffer).
	 */
	if (GIT_ADD_SIZET_OVERFLOW(&alloc_size, hdr.size, 1) ||
		(body = git__malloc(alloc_size)) == NULL) {
		error = -1;
		goto done;
	}

	assert(decompressed >= head_len);
	body_len = decompressed - head_len;

	if (body_len)
		memcpy(body, head + head_len, body_len);

	decompressed = hdr.size - body_len;
	if ((error = git_zstream_get_output(body + body_len, &decompressed, &zstream)) < 0)
		goto done;

	if (!git_zstream_done(&zstream)) {
		git_error_set(GIT_ERROR_ZLIB, "failed to finish zlib inflation: stream aborted prematurely");
		error = -1;
		goto done;
	}

	body[hdr.size] = '\0';

	out->data = body;
	out->len = hdr.size;
	out->type = hdr.type;

done:
	if (error < 0)
		git__free(body);

	git_zstream_free(&zstream);
	return error;
}