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
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_rawobj ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_stream ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int) ; 
 int git_odb_open_wstream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_odb_stream_finalize_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_stream_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_stream_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void streaming_write(git_oid *oid, git_odb *odb, git_rawobj *raw)
{
   git_odb_stream *stream;
   int error;

   cl_git_pass(git_odb_open_wstream(&stream, odb, raw->len, raw->type));
   git_odb_stream_write(stream, raw->data, raw->len);
   error = git_odb_stream_finalize_write(oid, stream);
   git_odb_stream_free(stream);
   cl_git_pass(error);
}