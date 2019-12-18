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
struct val_anchors {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  anchor_store_str (struct val_anchors*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  log_err (char*,int) ; 
 int readkeyword_bindfile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__* sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ *) ; 
 char* sldns_buffer_current (int /*<<< orphan*/ *) ; 
 int sldns_buffer_position (int /*<<< orphan*/ *) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sldns_buffer_write_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 

__attribute__((used)) static int
process_bind_contents(struct val_anchors* anchors, sldns_buffer* buf, 
	int* line, FILE* in)
{
	/* loop over contents, collate strings before ; */
	/* contents is (numbered): 0   1    2  3 4   5  6 7 8    */
	/*                           name. 257 3 5 base64 base64 */
	/* quoted value:           0 "111"  0  0 0   0  0 0 0    */
	/* comments value:         1 "000"  1  1  1 "0  0 0 0"  1 */
	int contnum = 0;
	int quoted = 0;
	int comments = 1;
	int rdlen;
	char* str = 0;
	sldns_buffer_clear(buf);
	while((rdlen=readkeyword_bindfile(in, buf, line, comments))) {
		if(rdlen == 1 && sldns_buffer_position(buf) == 1
			&& isspace((unsigned char)*sldns_buffer_begin(buf))) {
			/* starting whitespace is removed */
			sldns_buffer_clear(buf);
			continue;
		} else if(rdlen == 1 && sldns_buffer_current(buf)[-1] == '"') {
			/* remove " from the string */
			if(contnum == 0) {
				quoted = 1;
				comments = 0;
			}
			sldns_buffer_skip(buf, -1);
			if(contnum > 0 && quoted) {
				if(sldns_buffer_remaining(buf) < 8+1) {
					log_err("line %d, too long", *line);
					return 0;
				}
				sldns_buffer_write(buf, " DNSKEY ", 8);
				quoted = 0;
				comments = 1;
			} else if(contnum > 0)
				comments = !comments;
			continue;
		} else if(rdlen == 1 && sldns_buffer_current(buf)[-1] == ';') {

			if(contnum < 5) {
				sldns_buffer_write_u8(buf, 0);
				log_err("line %d, bad key", *line);
				return 0;
			}
			sldns_buffer_skip(buf, -1);
			sldns_buffer_write_u8(buf, 0);
			str = strdup((char*)sldns_buffer_begin(buf));
			if(!str) {
				log_err("line %d, allocation failure", *line);
				return 0;
			}
			if(!anchor_store_str(anchors, buf, str)) {
				log_err("line %d, bad key", *line);
				free(str);
				return 0;
			}
			free(str);
			sldns_buffer_clear(buf);
			contnum = 0;
			quoted = 0;
			comments = 1;
			continue;
		} else if(rdlen == 1 && sldns_buffer_current(buf)[-1] == '}') {
			if(contnum > 0) {
				sldns_buffer_write_u8(buf, 0);
				log_err("line %d, bad key before }", *line);
				return 0;
			}
			return 1;
		} else if(rdlen == 1 && 
			isspace((unsigned char)sldns_buffer_current(buf)[-1])) {
			/* leave whitespace here */
		} else {
			/* not space or whatnot, so actual content */
			contnum ++;
			if(contnum == 1 && !quoted) {
				if(sldns_buffer_remaining(buf) < 8+1) {
					log_err("line %d, too long", *line);
					return 0;
				}	
				sldns_buffer_write(buf, " DNSKEY ", 8);
			}
		}
	}

	log_err("line %d, EOF before }", *line);
	return 0;
}