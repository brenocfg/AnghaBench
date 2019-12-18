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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  log_err (char*,int,int) ; 
 int readkeyword_bindfile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__* sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_write_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
skip_to_special(FILE* in, sldns_buffer* buf, int* line, int spec) 
{
	int rdlen;
	sldns_buffer_clear(buf);
	while((rdlen=readkeyword_bindfile(in, buf, line, 1))) {
		if(rdlen == 1 && isspace((unsigned char)*sldns_buffer_begin(buf))) {
			sldns_buffer_clear(buf);
			continue;
		}
		if(rdlen != 1 || *sldns_buffer_begin(buf) != (uint8_t)spec) {
			sldns_buffer_write_u8(buf, 0);
			log_err("trusted-keys, line %d, expected %c", 
				*line, spec);
			return 0;
		}
		return 1;
	}
	log_err("trusted-keys, line %d, expected %c got EOF", *line, spec);
	return 0;
}