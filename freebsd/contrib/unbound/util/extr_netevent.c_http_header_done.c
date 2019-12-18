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
 size_t sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_position (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_read_u8_at (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
http_header_done(sldns_buffer* buf)
{
	size_t i;
	for(i=sldns_buffer_position(buf); i<sldns_buffer_limit(buf); i++) {
		/* there was a \r before the \n, but we ignore that */
		if((char)sldns_buffer_read_u8_at(buf, i) == '\n')
			return 1;
	}
	return 0;
}