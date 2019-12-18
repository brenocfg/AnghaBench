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
 size_t sldns_buffer_position (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_read_u8_at (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
chunkline_remove_trailcomment(sldns_buffer* buf, size_t start)
{
	size_t end = sldns_buffer_position(buf);
	size_t i;
	int squote = 0, dquote = 0;
	for(i=start; i<end; i++) {
		char c = (char)sldns_buffer_read_u8_at(buf, i);
		if(squote && c != '\'') continue;
		if(dquote && c != '"') continue;
		if(c == '"')
			dquote = !dquote; /* skip quoted part */
		else if(c == '\'')
			squote = !squote; /* skip quoted part */
		else if(c == ';') {
			/* rest is a comment */
			sldns_buffer_set_position(buf, i);
			return;
		}
	}
	/* nothing to remove */
}