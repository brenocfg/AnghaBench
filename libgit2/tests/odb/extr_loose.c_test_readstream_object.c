#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ object_data ;
struct TYPE_8__ {size_t len; char* data; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ git_rawobj ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_stream ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_objects (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_odb_open_rstream (int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_stream_free (int /*<<< orphan*/ *) ; 
 int git_odb_stream_read (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_object_files (TYPE_1__*) ; 

__attribute__((used)) static void test_readstream_object(object_data *data, size_t blocksize)
{
	git_oid id;
	git_odb *odb;
	git_odb_stream *stream;
	git_rawobj tmp;
	char buf[2048], *ptr = buf;
	size_t remain;
	int ret;

	write_object_files(data);

	cl_git_pass(git_odb_open(&odb, "test-objects"));
	cl_git_pass(git_oid_fromstr(&id, data->id));
	cl_git_pass(git_odb_open_rstream(&stream, &tmp.len, &tmp.type, odb, &id));

	remain = tmp.len;

	while (remain) {
		cl_assert((ret = git_odb_stream_read(stream, ptr, blocksize)) >= 0);
		if (ret == 0)
			break;

		cl_assert(remain >= (size_t)ret);
		remain -= ret;
		ptr += ret;
	}

	cl_assert(remain == 0);

	tmp.data = buf;

	cmp_objects(&tmp, data);

	git_odb_stream_free(stream);
	git_odb_free(odb);
}