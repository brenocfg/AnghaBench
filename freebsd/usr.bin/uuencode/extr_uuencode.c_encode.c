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
 int ENC (char) ; 
 scalar_t__ EOF ; 
 char** av ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ fputc (char,int /*<<< orphan*/ ) ; 
 int fread (char*,int,int,int /*<<< orphan*/ ) ; 
 int mode ; 
 int /*<<< orphan*/  output ; 
 int /*<<< orphan*/  raw ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static void
encode(void)
{
	register int ch, n;
	register char *p;
	char buf[80];

	if (!raw)
		(void)fprintf(output, "begin %o %s\n", mode, *av);
	while ((n = fread(buf, 1, 45, stdin))) {
		ch = ENC(n);
		if (fputc(ch, output) == EOF)
			break;
		for (p = buf; n > 0; n -= 3, p += 3) {
			/* Pad with nulls if not a multiple of 3. */
			if (n < 3) {
				p[2] = '\0';
				if (n < 2)
					p[1] = '\0';
			}
			ch = *p >> 2;
			ch = ENC(ch);
			if (fputc(ch, output) == EOF)
				break;
			ch = ((*p << 4) & 060) | ((p[1] >> 4) & 017);
			ch = ENC(ch);
			if (fputc(ch, output) == EOF)
				break;
			ch = ((p[1] << 2) & 074) | ((p[2] >> 6) & 03);
			ch = ENC(ch);
			if (fputc(ch, output) == EOF)
				break;
			ch = p[2] & 077;
			ch = ENC(ch);
			if (fputc(ch, output) == EOF)
				break;
		}
		if (fputc('\n', output) == EOF)
			break;
	}
	if (ferror(stdin))
		errx(1, "read error");
	if (!raw)
		(void)fprintf(output, "%c\nend\n", ENC('\0'));
}