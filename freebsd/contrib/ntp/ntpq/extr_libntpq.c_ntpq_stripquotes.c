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
typedef  int u_char ;

/* Variables and functions */

int ntpq_stripquotes ( char *resultbuf, char *srcbuf, int datalen, int maxlen )
{
	char* dst = resultbuf;
	char* dep = resultbuf + maxlen - 1;
	char* src = srcbuf;
	char* sep = srcbuf + (datalen >= 0 ? datalen : 0); 
	int   esc = 0;
	int   ch;
	
	if (maxlen <= 0)
		return 0;
	
	while ((dst != dep) && (src != sep) && (ch = (u_char)*src++) != 0) {
		if (esc) {
			esc = 0;
			switch (ch) {
				/* skip and do not copy */
				/* case '"':*/ /* quotes */
			case 'n': /*newline*/
			case 'r': /*carriage return*/
			case 'g': /*bell*/
			case 't': /*tab*/
				continue;
			default:
				break;
			}
		} else {
			switch (ch) {
			case '\\':
				esc = 1;
			case '"':
				continue;
			default:
				break;
			}
		}
		*dst++ = (char)ch;
	}
	*dst = '\0';
	return (int)(dst - resultbuf);
}