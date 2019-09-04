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
struct compress_stream {TYPE_1__* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (TYPE_1__*,char*,int) ;} ;

/* Variables and functions */
 int CHUNKSIZE ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*,int) ; 

__attribute__((used)) static int compress_stream_write__inflated(struct compress_stream *stream, const char *buffer, size_t len)
{
	char inflated[CHUNKSIZE];
	size_t i, j;

	for (i = 0; i < len; i++) {
		for (j = 0; j < CHUNKSIZE; j++)
			inflated[j] = buffer[i];

		cl_git_pass(stream->next->write(stream->next, inflated, CHUNKSIZE));
	}

	return 0;
}