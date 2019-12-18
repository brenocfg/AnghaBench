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
typedef  int uint32_t ;
typedef  int u_int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  hexbyte (char*,int const) ; 
 int /*<<< orphan*/  puts (char*) ; 

__attribute__((used)) static void
hexdump(const uint8_t *region, uint32_t len)
{
	const uint8_t *line;
	char linebuf[128];
	int i;
	int x;
	int c;

	for (line = region; line < (region + len); line += 16) {

		i = 0;

		linebuf[i] = ' ';
		hexbyte(linebuf + i + 1, ((line - region) >> 8) & 0xFF);
		hexbyte(linebuf + i + 3, (line - region) & 0xFF);
		linebuf[i + 5] = ' ';
		linebuf[i + 6] = ' ';
		i += 7;

		for (x = 0; x < 16; x++) {
		  if ((line + x) < (region + len)) {
			hexbyte(linebuf + i,
			    *(const u_int8_t *)(line + x));
		  } else {
			  linebuf[i] = '-';
			  linebuf[i + 1] = '-';
			}
			linebuf[i + 2] = ' ';
			if (x == 7) {
			  linebuf[i + 3] = ' ';
			  i += 4;
			} else {
			  i += 3;
			}
		}
		linebuf[i] = ' ';
		linebuf[i + 1] = '|';
		i += 2;
		for (x = 0; x < 16; x++) {
			if ((line + x) < (region + len)) {
				c = *(const u_int8_t *)(line + x);
				/* !isprint(c) */
				if ((c < ' ') || (c > '~'))
					c = '.';
				linebuf[i] = c;
			} else {
				linebuf[i] = ' ';
			}
			i++;
		}
		linebuf[i] = '|';
		linebuf[i + 1] = 0;
		i += 2;
		puts(linebuf);
	}
}