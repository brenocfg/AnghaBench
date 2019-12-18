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
typedef  size_t uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 size_t* reversebits ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
verbose_dump_buffer(void *pbuf, int icount, int lsb)
{
	uint8_t	ch;
	int	ictr, ictr2, idx;

	fputs("        |  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F "
	      "|                  |\n", stderr);

	for (ictr = 0; ictr < icount; ictr += 16) {
		fprintf(stderr, " %6x | ", ictr & 0xfffff0);

		for (ictr2 = 0; ictr2 < 16; ictr2++) {
			idx = ictr + ictr2;

			if (idx < icount) {
				ch = ((uint8_t *) pbuf)[idx];

				if (lsb)
					ch = reversebits[ch];

				fprintf(stderr, "%02hhx ", ch);
			}
			else {
				fputs("   ", stderr);
			}
		}

		fputs("| ", stderr);

		for (ictr2 = 0; ictr2 < 16; ictr2++) {
			idx = ictr + ictr2;

			if (idx < icount) {
				ch = ((uint8_t *) pbuf)[idx];

				if (lsb)
					ch = reversebits[ch];

				if (ch < ' ' || ch > 127)
					goto out_of_range;

				fprintf(stderr, "%c", ch);
			}
			else if (idx < icount) {
		out_of_range:
				fputc('.', stderr);
			}
			else {
				fputc(' ', stderr);
			}
		}

		fputs(" |\n", stderr);
	}

	fflush(stderr);
}