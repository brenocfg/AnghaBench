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
struct sbuf {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  sbuf_bcat (struct sbuf*,char const*,int) ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int sbuf_finish (struct sbuf*) ; 
 scalar_t__ sbuf_len (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,char,char) ; 

__attribute__((used)) static int
led_parse(const char *s, struct sbuf **sb, int *state)
{
	int i, error;

	/*
	 * Handle "on" and "off" immediately so people can flash really
	 * fast from userland if they want to
	 */
	if (*s == '0' || *s == '1') {
		*state = *s & 1;
		return (0);
	}

	*state = 0;
	*sb = sbuf_new_auto();
	if (*sb == NULL)
		return (ENOMEM);
	switch(s[0]) {
		/*
		 * Flash, default is 100msec/100msec.
		 * 'f2' sets 200msec/200msec etc.
		 */
		case 'f':
			if (s[1] >= '1' && s[1] <= '9')
				i = s[1] - '1';
			else
				i = 0;
			sbuf_printf(*sb, "%c%c", 'A' + i, 'a' + i);
			break;
		/*
		 * Digits, flashes out numbers.
		 * 'd12' becomes -__________-_-______________________________
		 */
		case 'd':
			for(s++; *s; s++) {
				if (!isdigit(*s))
					continue;
				i = *s - '0';
				if (i == 0)
					i = 10;
				for (; i > 1; i--) 
					sbuf_cat(*sb, "Aa");
				sbuf_cat(*sb, "Aj");
			}
			sbuf_cat(*sb, "jj");
			break;
		/*
		 * String, roll your own.
		 * 'a-j' gives "off" for n/10 sec.
		 * 'A-J' gives "on" for n/10 sec.
		 * no delay before repeat
		 * 'sAaAbBa' becomes _-_--__-
		 */
		case 's':
			for(s++; *s; s++) {
				if ((*s >= 'a' && *s <= 'j') ||
				    (*s >= 'A' && *s <= 'J') ||
				    *s == 'U' || *s <= 'u' ||
					*s == '.')
					sbuf_bcat(*sb, s, 1);
			}
			break;
		/*
		 * Morse.
		 * '.' becomes _-
		 * '-' becomes _---
		 * ' ' becomes __
		 * '\n' becomes ____
		 * 1sec pause between repeats
		 * '... --- ...' -> _-_-_-___---_---_---___-_-_-__________
		 */
		case 'm':
			for(s++; *s; s++) {
				if (*s == '.')
					sbuf_cat(*sb, "aA");
				else if (*s == '-')
					sbuf_cat(*sb, "aC");
				else if (*s == ' ')
					sbuf_cat(*sb, "b");
				else if (*s == '\n')
					sbuf_cat(*sb, "d");
			}
			sbuf_cat(*sb, "j");
			break;
		default:
			sbuf_delete(*sb);
			return (EINVAL);
	}
	error = sbuf_finish(*sb);
	if (error != 0 || sbuf_len(*sb) == 0) {
		*sb = NULL;
		return (error);
	}
	return (0);
}