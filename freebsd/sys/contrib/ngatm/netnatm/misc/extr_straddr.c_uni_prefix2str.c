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
typedef  int u_int ;
typedef  int u_char ;

/* Variables and functions */

void
uni_prefix2str(char *out, const u_char *in, u_int len, int dotit)
{
	static char hex[16] = "0123456789abcdef";
	static int fmt[3][6] = {
		{ 1, 2, 10, 6, 1, 0 },
		{ 1, 2, 10, 6, 1, 0 },
		{ 1, 8,  4, 6, 1, 0 },
	};
	int f, b;
	u_int i;

	if (len > 20)
		len = 20;

	if(dotit) {
		switch(*in) {

		  case 0x39:	/* DCC */
			i = 0;
  fmt:
			for(f = 0; fmt[i][f]; f++) {
				if (len == 0)
					goto done;
				if(f != 0)
					*out++ = '.';
				for(b = 0; b < fmt[i][f]; b++) {
					if (len-- == 0)
						goto done;
					*out++ = hex[(*in >> 4) & 0xf];
					*out++ = hex[*in & 0xf];
					in++;
				}
			}
  done:
			*out = '\0';
			return;

		  case 0x47:	/* ICD */
			i = 1;
			goto fmt;

		  case 0x45:	/* E.164 */
			i = 2;
			goto fmt;
		}
	}

	/* undotted */
	for(i = 0; i < len; i++) {
		*out++ = hex[(*in >> 4) & 0xf];
		*out++ = hex[*in & 0xf];
		in++;
	}
	*out = '\0';
}