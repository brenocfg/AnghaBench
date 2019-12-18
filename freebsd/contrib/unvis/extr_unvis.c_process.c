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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int UNVIS_END ; 
#define  UNVIS_NOCHAR 131 
#define  UNVIS_SYNBAD 130 
#define  UNVIS_VALID 129 
#define  UNVIS_VALIDPUSH 128 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int const unvis (char*,char,int*,int) ; 
 int /*<<< orphan*/  warnx (char*,char const*,int) ; 

__attribute__((used)) static void
process(FILE *fp, const char *filename, int eflags)
{
	int offset = 0, c, ret;
	int state = 0;
	char outc;

	while ((c = getc(fp)) != EOF) {
		offset++;
	again:
		switch(ret = unvis(&outc, (char)c, &state, eflags)) {
		case UNVIS_VALID:
			(void)putchar(outc);
			break;
		case UNVIS_VALIDPUSH:
			(void)putchar(outc);
			goto again;
		case UNVIS_SYNBAD:
			warnx("%s: offset: %d: can't decode", filename, offset);
			state = 0;
			break;
		case 0:
		case UNVIS_NOCHAR:
			break;
		default:
			errx(1, "bad return value (%d), can't happen", ret);
			/* NOTREACHED */
		}
	}
	if (unvis(&outc, (char)0, &state, eflags | UNVIS_END) == UNVIS_VALID)
		(void)putchar(outc);
}