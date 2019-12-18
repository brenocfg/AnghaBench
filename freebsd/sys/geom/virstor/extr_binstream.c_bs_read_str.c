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
struct TYPE_3__ {char* data; int pos; } ;
typedef  TYPE_1__ bin_stream_t ;

/* Variables and functions */

char*
bs_read_str(bin_stream_t * bs, char *buf, unsigned buf_size)
{
	unsigned	len = 0;
	char           *work_buf = buf;
	if (buf == NULL || buf_size < 1)
		return NULL;
	do {
		*work_buf = *(bs->data + bs->pos + len);
	} while (len++ < buf_size - 1 && *(work_buf++) != '\0');
	*(buf + buf_size - 1) = '\0';
	bs->pos += len;
	return buf;
}