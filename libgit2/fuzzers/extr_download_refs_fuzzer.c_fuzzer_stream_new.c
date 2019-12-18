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
struct TYPE_2__ {int /*<<< orphan*/  free; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct fuzzer_stream {TYPE_1__ base; scalar_t__ endp; scalar_t__ readp; } ;
struct fuzzer_buffer {scalar_t__ size; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  fuzzer_stream_free ; 
 int /*<<< orphan*/  fuzzer_stream_read ; 
 int /*<<< orphan*/  fuzzer_stream_write ; 
 struct fuzzer_stream* malloc (int) ; 

__attribute__((used)) static int fuzzer_stream_new(
	struct fuzzer_stream **out,
	const struct fuzzer_buffer *data)
{
	struct fuzzer_stream *stream = malloc(sizeof(*stream));
	if (!stream)
		return -1;

	stream->readp = data->data;
	stream->endp = data->data + data->size;
	stream->base.read = fuzzer_stream_read;
	stream->base.write = fuzzer_stream_write;
	stream->base.free = fuzzer_stream_free;

	*out = stream;

	return 0;
}