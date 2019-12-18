#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_writestream ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int git_blob_create_from_stream_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_blob_create_fromstream_commit(
	git_oid *out,
	git_writestream *stream)
{
	return git_blob_create_from_stream_commit(out, stream);
}