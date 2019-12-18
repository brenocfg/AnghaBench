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
 size_t H_ATTR_OFFSET ; 
 size_t H_LEVEL_OFFSET ; 
 int H_METHOD_OFFSET ; 

__attribute__((used)) static size_t
lha_check_header_format(const void *h)
{
	const unsigned char *p = h;
	size_t next_skip_bytes;

	switch (p[H_METHOD_OFFSET+3]) {
	/*
	 * "-lh0-" ... "-lh7-" "-lhd-"
	 * "-lzs-" "-lz5-"
	 */
	case '0': case '1': case '2': case '3':
	case '4': case '5': case '6': case '7':
	case 'd':
	case 's':
		next_skip_bytes = 4;

		/* b0 == 0 means the end of an LHa archive file.	*/
		if (p[0] == 0)
			break;
		if (p[H_METHOD_OFFSET] != '-' || p[H_METHOD_OFFSET+1] != 'l'
		    ||  p[H_METHOD_OFFSET+4] != '-')
			break;

		if (p[H_METHOD_OFFSET+2] == 'h') {
			/* "-lh?-" */
			if (p[H_METHOD_OFFSET+3] == 's')
				break;
			if (p[H_LEVEL_OFFSET] == 0)
				return (0);
			if (p[H_LEVEL_OFFSET] <= 3 && p[H_ATTR_OFFSET] == 0x20)
				return (0);
		}
		if (p[H_METHOD_OFFSET+2] == 'z') {
			/* LArc extensions: -lzs-,-lz4- and -lz5- */
			if (p[H_LEVEL_OFFSET] != 0)
				break;
			if (p[H_METHOD_OFFSET+3] == 's'
			    || p[H_METHOD_OFFSET+3] == '4'
			    || p[H_METHOD_OFFSET+3] == '5')
				return (0);
		}
		break;
	case 'h': next_skip_bytes = 1; break;
	case 'z': next_skip_bytes = 1; break;
	case 'l': next_skip_bytes = 2; break;
	case '-': next_skip_bytes = 3; break;
	default : next_skip_bytes = 4; break;
	}

	return (next_skip_bytes);
}