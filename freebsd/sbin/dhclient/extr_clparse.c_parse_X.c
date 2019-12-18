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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int COLON ; 
 int NUMBER ; 
 int NUMBER_OR_NAME ; 
 int STRING ; 
 int /*<<< orphan*/  convert_num (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int next_token (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_warn (char*) ; 
 int peek_token (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_to_semi (int /*<<< orphan*/ *) ; 
 unsigned int strlen (char*) ; 

unsigned
parse_X(FILE *cfile, u_int8_t *buf, unsigned max)
{
	int	 token;
	char	*val;
	unsigned len;

	token = peek_token(&val, cfile);
	if (token == NUMBER_OR_NAME || token == NUMBER) {
		len = 0;
		do {
			token = next_token(&val, cfile);
			if (token != NUMBER && token != NUMBER_OR_NAME) {
				parse_warn("expecting hexadecimal constant.");
				skip_to_semi(cfile);
				return (0);
			}
			convert_num(&buf[len], val, 16, 8);
			if (len++ > max) {
				parse_warn("hexadecimal constant too long.");
				skip_to_semi(cfile);
				return (0);
			}
			token = peek_token(&val, cfile);
			if (token == COLON)
				token = next_token(&val, cfile);
		} while (token == COLON);
		val = (char *)buf;
	} else if (token == STRING) {
		token = next_token(&val, cfile);
		len = strlen(val);
		if (len + 1 > max) {
			parse_warn("string constant too long.");
			skip_to_semi(cfile);
			return (0);
		}
		memcpy(buf, val, len + 1);
	} else {
		parse_warn("expecting string or hexadecimal data");
		skip_to_semi(cfile);
		return (0);
	}
	return (len);
}