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
typedef  int /*<<< orphan*/  header ;
struct TYPE_5__ {char* data; size_t len; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_rawobj ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_6__ {char* data; size_t len; } ;
typedef  TYPE_2__ git_buf_vec ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_hash_vec (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  git_object_typeisloose (int /*<<< orphan*/ ) ; 
 int git_odb__format_object_header (size_t*,char*,int,size_t,int /*<<< orphan*/ ) ; 

int git_odb__hashobj(git_oid *id, git_rawobj *obj)
{
	git_buf_vec vec[2];
	char header[64];
	size_t hdrlen;
	int error;

	assert(id && obj);

	if (!git_object_typeisloose(obj->type)) {
		git_error_set(GIT_ERROR_INVALID, "invalid object type");
		return -1;
	}

	if (!obj->data && obj->len != 0) {
		git_error_set(GIT_ERROR_INVALID, "invalid object");
		return -1;
	}

	if ((error = git_odb__format_object_header(&hdrlen,
		header, sizeof(header), obj->len, obj->type)) < 0)
		return error;

	vec[0].data = header;
	vec[0].len = hdrlen;
	vec[1].data = obj->data;
	vec[1].len = obj->len;

	return git_hash_vec(id, vec, 2);
}