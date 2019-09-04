#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t offset; } ;
typedef  TYPE_1__ gitno_buffer ;
typedef  int /*<<< orphan*/  git_smart_subtransport_stream ;
struct TYPE_7__ {int /*<<< orphan*/  io; int /*<<< orphan*/  sent_command; } ;
typedef  TYPE_2__ git_proto_stream ;

/* Variables and functions */
 int /*<<< orphan*/  gitno_buffer_setup_fromstream (int /*<<< orphan*/ ,TYPE_1__*,char*,size_t) ; 
 int gitno_recv (TYPE_1__*) ; 
 int send_command (TYPE_2__*) ; 

__attribute__((used)) static int git_proto_stream_read(
	git_smart_subtransport_stream *stream,
	char *buffer,
	size_t buf_size,
	size_t *bytes_read)
{
	int error;
	git_proto_stream *s = (git_proto_stream *)stream;
	gitno_buffer buf;

	*bytes_read = 0;

	if (!s->sent_command && (error = send_command(s)) < 0)
		return error;

	gitno_buffer_setup_fromstream(s->io, &buf, buffer, buf_size);

	if ((error = gitno_recv(&buf)) < 0)
		return error;

	*bytes_read = buf.offset;

	return 0;
}