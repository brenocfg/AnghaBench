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

unsigned
bs_write_buf(bin_stream_t * bs, char *data, unsigned data_size)
{
	unsigned	i;
	for (i = 0; i < data_size; i++)
		*(bs->data + bs->pos + i) = *(data + i);
	bs->pos += data_size;
	return bs->pos;
}