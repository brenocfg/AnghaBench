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

/* Variables and functions */
 int EINVAL ; 
#define  T_EOF 132 
#define  T_LBRACE 131 
#define  T_LBRACKET 130 
#define  T_RBRACE 129 
#define  T_RBRACKET 128 
 int ng_parse_get_token (char const*,int*,int*) ; 

__attribute__((used)) static int
ng_parse_skip_value(const char *s, int off0, int *lenp)
{
	int len, nbracket, nbrace;
	int off = off0;

	len = nbracket = nbrace = 0;
	do {
		switch (ng_parse_get_token(s, &off, &len)) {
		case T_LBRACKET:
			nbracket++;
			break;
		case T_LBRACE:
			nbrace++;
			break;
		case T_RBRACKET:
			if (nbracket-- == 0)
				return (EINVAL);
			break;
		case T_RBRACE:
			if (nbrace-- == 0)
				return (EINVAL);
			break;
		case T_EOF:
			return (EINVAL);
		default:
			break;
		}
		off += len;
	} while (nbracket > 0 || nbrace > 0);
	*lenp = off - off0;
	return (0);
}