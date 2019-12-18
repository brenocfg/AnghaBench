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
 scalar_t__ sldns_buffer_read_u8_at (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
chunkline_is_comment_line_or_empty(sldns_buffer* buf)
{
	size_t i, end = sldns_buffer_limit(buf);
	for(i=0; i<end; i++) {
		char c = (char)sldns_buffer_read_u8_at(buf, i);
		if(c == ';')
			return 1; /* comment */
		else if(c != ' ' && c != '\t' && c != '\r' && c != '\n')
			return 0; /* not a comment */
	}
	return 1; /* empty */
}