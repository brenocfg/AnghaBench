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
typedef  int /*<<< orphan*/  git_writestream ;
struct TYPE_3__ {struct TYPE_3__* hintpath; int /*<<< orphan*/  fbuf; } ;
typedef  TYPE_1__ blob_writestream ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_filebuf_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blob_writestream_free(git_writestream *_stream)
{
	blob_writestream *stream = (blob_writestream *) _stream;

	git_filebuf_cleanup(&stream->fbuf);
	git__free(stream->hintpath);
	git__free(stream);
}