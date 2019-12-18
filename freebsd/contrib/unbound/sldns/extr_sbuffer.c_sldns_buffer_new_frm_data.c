#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t _limit; size_t _capacity; int _status_err; scalar_t__ _data; scalar_t__ _fixed; scalar_t__ _vfixed; scalar_t__ _position; } ;
typedef  TYPE_1__ sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_invariant (TYPE_1__*) ; 

void
sldns_buffer_new_frm_data(sldns_buffer *buffer, void *data, size_t size)
{
	assert(data != NULL);

	buffer->_position = 0; 
	buffer->_limit = buffer->_capacity = size;
	buffer->_fixed = 0;
	buffer->_vfixed = 0;
	if (!buffer->_fixed && buffer->_data)
		free(buffer->_data);
	buffer->_data = malloc(size);
	if(!buffer->_data) {
		buffer->_status_err = 1;
		return;
	}
	memcpy(buffer->_data, data, size);
	buffer->_status_err = 0;
	
	sldns_buffer_invariant(buffer);
}