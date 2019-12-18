#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 scalar_t__* ldns_buffer_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_buffer_set_capacity (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_buffer_write_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 

char *
ldns_buffer2str(ldns_buffer *buffer)
{
	char *str;

	/* check if buffer ends with \0, if not, and
	   if there is space, add it */
	if (*(ldns_buffer_at(buffer, ldns_buffer_position(buffer))) != 0) {
		if (!ldns_buffer_reserve(buffer, 1)) {
			return NULL;
		}
		ldns_buffer_write_u8(buffer, (uint8_t) '\0');
		if (!ldns_buffer_set_capacity(buffer, ldns_buffer_position(buffer))) {
			return NULL;
		}
	}

	str = strdup((const char *)ldns_buffer_begin(buffer));
        if(!str) {
                return NULL;
        }
	return str;
}