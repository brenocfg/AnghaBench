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
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 char* ldns_buffer_export (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_buffer_set_capacity (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_buffer_write_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

char *
ldns_buffer_export2str(ldns_buffer *buffer)
{
	/* Append '\0' as string terminator */
	if (! ldns_buffer_reserve(buffer, 1)) {
		return NULL;
	}
	ldns_buffer_write_u8(buffer, 0);

	/* reallocate memory to the size of the string and export */
	ldns_buffer_set_capacity(buffer, ldns_buffer_position(buffer));
	return ldns_buffer_export(buffer);
}