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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  hexstr2bin (char const*,int*,int) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 
 char* os_realloc (char*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static char * json_parse_string(const char **json_pos, const char *end)
{
	const char *pos = *json_pos;
	char *str, *spos, *s_end;
	size_t max_len, buf_len;
	u8 bin[2];

	pos++; /* skip starting quote */

	max_len = end - pos + 1;
	buf_len = max_len > 10 ? 10 : max_len;
	str = os_malloc(buf_len);
	if (!str)
		return NULL;
	spos = str;
	s_end = str + buf_len;

	for (; pos < end; pos++) {
		if (buf_len < max_len && s_end - spos < 3) {
			char *tmp;
			int idx;

			idx = spos - str;
			buf_len *= 2;
			if (buf_len > max_len)
				buf_len = max_len;
			tmp = os_realloc(str, buf_len);
			if (!tmp)
				goto fail;
			str = tmp;
			spos = str + idx;
			s_end = str + buf_len;
		}

		switch (*pos) {
		case '\"': /* end string */
			*spos = '\0';
			/* caller will move to the next position */
			*json_pos = pos;
			return str;
		case '\\':
			pos++;
			if (pos >= end) {
				wpa_printf(MSG_DEBUG,
					   "JSON: Truncated \\ escape");
				goto fail;
			}
			switch (*pos) {
			case '"':
			case '\\':
			case '/':
				*spos++ = *pos;
				break;
			case 'n':
				*spos++ = '\n';
				break;
			case 'r':
				*spos++ = '\r';
				break;
			case 't':
				*spos++ = '\t';
				break;
			case 'u':
				if (end - pos < 5 ||
				    hexstr2bin(pos + 1, bin, 2) < 0 ||
				    bin[1] == 0x00) {
					wpa_printf(MSG_DEBUG,
						   "JSON: Invalid \\u escape");
					goto fail;
				}
				if (bin[0] == 0x00) {
					*spos++ = bin[1];
				} else {
					*spos++ = bin[0];
					*spos++ = bin[1];
				}
				pos += 4;
				break;
			default:
				wpa_printf(MSG_DEBUG,
					   "JSON: Unknown escape '%c'", *pos);
				goto fail;
			}
			break;
		default:
			*spos++ = *pos;
			break;
		}
	}

fail:
	os_free(str);
	return NULL;
}