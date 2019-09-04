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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  git_packfile_stream ;
struct TYPE_3__ {int /*<<< orphan*/  objbuf; } ;
typedef  TYPE_1__ git_indexer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ git_packfile_stream_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int read_object_stream(git_indexer *idx, git_packfile_stream *stream)
{
	ssize_t read;

	assert(stream);

	do {
		read = git_packfile_stream_read(stream, idx->objbuf, sizeof(idx->objbuf));
	} while (read > 0);

	if (read < 0)
		return (int)read;

	return 0;
}