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
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 size_t sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_read_u8_at (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_set_limit (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_write_u8_at (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chunkline_newline_removal(sldns_buffer* buf)
{
	size_t i, end=sldns_buffer_limit(buf);
	for(i=0; i<end; i++) {
		char c = (char)sldns_buffer_read_u8_at(buf, i);
		if(c == '\n' && i==end-1) {
			sldns_buffer_write_u8_at(buf, i, 0);
			sldns_buffer_set_limit(buf, end-1);
			return;
		}
		if(c == '\n')
			sldns_buffer_write_u8_at(buf, i, (uint8_t)' ');
	}
}