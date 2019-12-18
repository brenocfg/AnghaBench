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
struct TYPE_3__ {char* data; size_t len; int /*<<< orphan*/ * cb_data; int /*<<< orphan*/  recv; scalar_t__ offset; } ;
typedef  TYPE_1__ gitno_buffer ;
typedef  int /*<<< orphan*/  git_stream ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int,size_t) ; 
 int /*<<< orphan*/  recv_stream ; 

void gitno_buffer_setup_fromstream(git_stream *st, gitno_buffer *buf, char *data, size_t len)
{
	memset(data, 0x0, len);
	buf->data = data;
	buf->len = len;
	buf->offset = 0;
	buf->recv = recv_stream;
	buf->cb_data = st;
}