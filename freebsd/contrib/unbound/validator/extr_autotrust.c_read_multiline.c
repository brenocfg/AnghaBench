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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__* strchr (char*,char) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int
read_multiline(char* buf, size_t len, FILE* in, int* linenr)
{
	char* pos = buf;
	size_t left = len;
	int depth = 0;
	buf[len-1] = 0;
	while(left > 0 && fgets(pos, (int)left, in) != NULL) {
		size_t i, poslen = strlen(pos);
		(*linenr)++;

		/* check what the new depth is after the line */
		/* this routine cannot handle braces inside quotes,
		   say for TXT records, but this routine only has to read keys */
		for(i=0; i<poslen; i++) {
			if(pos[i] == '(') {
				depth++;
			} else if(pos[i] == ')') {
				if(depth == 0) {
					log_err("mismatch: too many ')'");
					return -1;
				}
				depth--;
			} else if(pos[i] == ';') {
				break;
			}
		}

		/* normal oneline or last line: keeps newline and comments */
		if(depth == 0) {
			return 1;
		}

		/* more lines expected, snip off comments and newline */
		if(poslen>0) 
			pos[poslen-1] = 0; /* strip newline */
		if(strchr(pos, ';')) 
			strchr(pos, ';')[0] = 0; /* strip comments */

		/* move to paste other lines behind this one */
		poslen = strlen(pos);
		pos += poslen;
		left -= poslen;
		/* the newline is changed into a space */
		if(left <= 2 /* space and eos */) {
			log_err("line too long");
			return -1;
		}
		pos[0] = ' ';
		pos[1] = 0;
		pos += 1;
		left -= 1;
	}
	if(depth != 0) {
		log_err("mismatch: too many '('");
		return -1;
	}
	if(pos != buf)
		return 1;
	return 0;
}