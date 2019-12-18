#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fbuf; } ;
typedef  TYPE_1__ loose_writestream ;
typedef  int /*<<< orphan*/  git_odb_stream ;

/* Variables and functions */
 int git_filebuf_write (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static int loose_backend__writestream_write(git_odb_stream *_stream, const char *data, size_t len)
{
	loose_writestream *stream = (loose_writestream *)_stream;
	return git_filebuf_write(&stream->fbuf, data, len);
}