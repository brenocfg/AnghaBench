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
struct TYPE_3__ {int _fixed; void* _data; } ;
typedef  TYPE_1__ sldns_buffer ;

/* Variables and functions */

void *
sldns_buffer_export(sldns_buffer *buffer)
{
	buffer->_fixed = 1;
	return buffer->_data;
}