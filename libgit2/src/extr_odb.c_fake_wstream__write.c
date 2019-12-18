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
typedef  int /*<<< orphan*/  git_odb_stream ;
struct TYPE_2__ {scalar_t__ written; scalar_t__ size; scalar_t__ buffer; } ;
typedef  TYPE_1__ fake_wstream ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 

__attribute__((used)) static int fake_wstream__write(git_odb_stream *_stream, const char *data, size_t len)
{
	fake_wstream *stream = (fake_wstream *)_stream;

	assert(stream->written + len <= stream->size);

	memcpy(stream->buffer + stream->written, data, len);
	stream->written += len;
	return 0;
}