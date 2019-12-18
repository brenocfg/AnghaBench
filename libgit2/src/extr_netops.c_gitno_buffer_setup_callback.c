#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* data; size_t len; int (* recv ) (TYPE_1__*) ;void* cb_data; scalar_t__ offset; } ;
typedef  TYPE_1__ gitno_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int,size_t) ; 

void gitno_buffer_setup_callback(
	gitno_buffer *buf,
	char *data,
	size_t len,
	int (*recv)(gitno_buffer *buf), void *cb_data)
{
	memset(data, 0x0, len);
	buf->data = data;
	buf->len = len;
	buf->offset = 0;
	buf->recv = recv;
	buf->cb_data = cb_data;
}