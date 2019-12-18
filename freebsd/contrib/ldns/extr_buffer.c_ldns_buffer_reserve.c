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
struct TYPE_5__ {int _capacity; int _position; int _limit; int /*<<< orphan*/  _status; int /*<<< orphan*/  _fixed; } ;
typedef  TYPE_1__ ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ldns_buffer_invariant (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_buffer_set_capacity (TYPE_1__*,size_t) ; 

bool
ldns_buffer_reserve(ldns_buffer *buffer, size_t amount)
{
	ldns_buffer_invariant(buffer);
	assert(!buffer->_fixed);
	if (buffer->_capacity < buffer->_position + amount) {
		size_t new_capacity = buffer->_capacity * 3 / 2;

		if (new_capacity < buffer->_position + amount) {
			new_capacity = buffer->_position + amount;
		}
		if (!ldns_buffer_set_capacity(buffer, new_capacity)) {
			buffer->_status = LDNS_STATUS_MEM_ERR;
			return false;
		}
	}
	buffer->_limit = buffer->_capacity;
	return true;
}