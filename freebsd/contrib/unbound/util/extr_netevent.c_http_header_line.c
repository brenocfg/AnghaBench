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
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ sldns_buffer_current (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_position (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_read_u8_at (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_write_u8_at (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char*
http_header_line(sldns_buffer* buf)
{
	char* result = (char*)sldns_buffer_current(buf);
	size_t i;
	for(i=sldns_buffer_position(buf); i<sldns_buffer_limit(buf); i++) {
		/* terminate the string on the \r */
		if((char)sldns_buffer_read_u8_at(buf, i) == '\r')
			sldns_buffer_write_u8_at(buf, i, 0);
		/* terminate on the \n and skip past the it and done */
		if((char)sldns_buffer_read_u8_at(buf, i) == '\n') {
			sldns_buffer_write_u8_at(buf, i, 0);
			sldns_buffer_set_position(buf, i+1);
			return result;
		}
	}
	return NULL;
}