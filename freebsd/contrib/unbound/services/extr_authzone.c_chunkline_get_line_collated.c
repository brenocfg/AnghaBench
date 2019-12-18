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
struct auth_chunk {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 scalar_t__ chunkline_count_parens (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  chunkline_get_line (struct auth_chunk**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chunkline_remove_trailcomment (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_position (int /*<<< orphan*/ *) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_write_u8_at (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
chunkline_get_line_collated(struct auth_chunk** chunk, size_t* chunk_pos,
	sldns_buffer* buf)
{
	size_t pos;
	int parens = 0;
	sldns_buffer_clear(buf);
	pos = sldns_buffer_position(buf);
	if(!chunkline_get_line(chunk, chunk_pos, buf)) {
		if(sldns_buffer_position(buf) < sldns_buffer_limit(buf))
			sldns_buffer_write_u8_at(buf, sldns_buffer_position(buf), 0);
		else sldns_buffer_write_u8_at(buf, sldns_buffer_position(buf)-1, 0);
		sldns_buffer_flip(buf);
		return 0;
	}
	parens += chunkline_count_parens(buf, pos);
	while(parens > 0) {
		chunkline_remove_trailcomment(buf, pos);
		pos = sldns_buffer_position(buf);
		if(!chunkline_get_line(chunk, chunk_pos, buf)) {
			if(sldns_buffer_position(buf) < sldns_buffer_limit(buf))
				sldns_buffer_write_u8_at(buf, sldns_buffer_position(buf), 0);
			else sldns_buffer_write_u8_at(buf, sldns_buffer_position(buf)-1, 0);
			sldns_buffer_flip(buf);
			return 0;
		}
		parens += chunkline_count_parens(buf, pos);
	}

	if(sldns_buffer_remaining(buf) < 1) {
		verbose(VERB_ALGO, "http chunkline: "
			"line too long");
		return 0;
	}
	sldns_buffer_write_u8_at(buf, sldns_buffer_position(buf), 0);
	sldns_buffer_flip(buf);
	return 1;
}