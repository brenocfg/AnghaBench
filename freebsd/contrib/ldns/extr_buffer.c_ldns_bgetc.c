#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  _position; } ;
typedef  TYPE_1__ ldns_buffer ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  ldns_buffer_available_at (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ldns_buffer_limit (TYPE_1__*) ; 
 scalar_t__ ldns_buffer_read_u8 (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_buffer_set_position (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
ldns_bgetc(ldns_buffer *buffer)
{
	if (!ldns_buffer_available_at(buffer, buffer->_position, sizeof(uint8_t))) {
		ldns_buffer_set_position(buffer, ldns_buffer_limit(buffer));
		/* ldns_buffer_rewind(buffer);*/
		return EOF;
	}
	return (int)ldns_buffer_read_u8(buffer);
}