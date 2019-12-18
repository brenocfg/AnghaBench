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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  fatal_exit (char*,int) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ is_bind_special (int) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  skip_to_eol (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_position (int /*<<< orphan*/ *) ; 
 char sldns_buffer_read_u8_at (int /*<<< orphan*/ *,scalar_t__) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sldns_buffer_write_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
readkeyword_bindfile(FILE* in, sldns_buffer* buf, int* line, int comments)
{
	int c;
	int numdone = 0;
	while((c = getc(in)) != EOF ) {
		if(comments && c == '#') {	/*   # blabla   */
			skip_to_eol(in);
			(*line)++;
			continue;
		} else if(comments && c=='/' && numdone>0 && /* /_/ bla*/
			sldns_buffer_read_u8_at(buf, 
			sldns_buffer_position(buf)-1) == '/') {
			sldns_buffer_skip(buf, -1);
			numdone--;
			skip_to_eol(in);
			(*line)++;
			continue;
		} else if(comments && c=='*' && numdone>0 && /* /_* bla *_/ */
			sldns_buffer_read_u8_at(buf, 
			sldns_buffer_position(buf)-1) == '/') {
			sldns_buffer_skip(buf, -1);
			numdone--;
			/* skip to end of comment */
			while(c != EOF && (c=getc(in)) != EOF ) {
				if(c == '*') {
					if((c=getc(in)) == '/')
						break;
				}
				if(c == '\n')
					(*line)++;
			}
			continue;
		}
		/* not a comment, complete the keyword */
		if(numdone > 0) {
			/* check same type */
			if(isspace((unsigned char)c)) {
				ungetc(c, in);
				return numdone;
			}
			if(is_bind_special(c)) {
				ungetc(c, in);
				return numdone;
			}
		}
		if(c == '\n') {
			c = ' ';
			(*line)++;
		}
		/* space for 1 char + 0 string terminator */
		if(sldns_buffer_remaining(buf) < 2) {
			fatal_exit("trusted-keys, %d, string too long", *line);
		}
		sldns_buffer_write_u8(buf, (uint8_t)c);
		numdone++;
		if(isspace((unsigned char)c)) {
			/* collate whitespace into ' ' */
			while((c = getc(in)) != EOF ) {
				if(c == '\n')
					(*line)++;
				if(!isspace((unsigned char)c)) {
					ungetc(c, in);
					break;
				}
			}
			return numdone;
		}
		if(is_bind_special(c))
			return numdone;
	}
	return numdone;
}