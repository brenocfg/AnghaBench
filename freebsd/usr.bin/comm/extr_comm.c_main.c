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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/ * convert (char*) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * file (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 int iflag ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  show (int /*<<< orphan*/ *,char*,char const*,char**,size_t*) ; 
 int strcmp (char*,char*) ; 
 char** tabs ; 
 int /*<<< orphan*/  usage () ; 
 int wcscoll (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
main(int argc, char *argv[])
{
	int comp, read1, read2;
	int ch, flag1, flag2, flag3;
	FILE *fp1, *fp2;
	const char *col1, *col2, *col3;
	size_t line1len, line2len;
	char *line1, *line2;
	ssize_t n1, n2;
	wchar_t *tline1, *tline2;
	const char **p;

	(void) setlocale(LC_ALL, "");

	flag1 = flag2 = flag3 = 1;

	while ((ch = getopt(argc, argv, "123i")) != -1)
		switch(ch) {
		case '1':
			flag1 = 0;
			break;
		case '2':
			flag2 = 0;
			break;
		case '3':
			flag3 = 0;
			break;
		case 'i':
			iflag = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 2)
		usage();

	fp1 = file(argv[0]);
	fp2 = file(argv[1]);

	/* for each column printed, add another tab offset */
	p = tabs;
	col1 = col2 = col3 = NULL;
	if (flag1)
		col1 = *p++;
	if (flag2)
		col2 = *p++;
	if (flag3)
		col3 = *p;

	line1len = line2len = 0;
	line1 = line2 = NULL;
	n1 = n2 = -1;

	for (read1 = read2 = 1;;) {
		/* read next line, check for EOF */
		if (read1) {
			n1 = getline(&line1, &line1len, fp1);
			if (n1 < 0 && ferror(fp1))
				err(1, "%s", argv[0]);
			if (n1 > 0 && line1[n1 - 1] == '\n')
				line1[n1 - 1] = '\0';

		}
		if (read2) {
			n2 = getline(&line2, &line2len, fp2);
			if (n2 < 0 && ferror(fp2))
				err(1, "%s", argv[1]);
			if (n2 > 0 && line2[n2 - 1] == '\n')
				line2[n2 - 1] = '\0';
		}

		/* if one file done, display the rest of the other file */
		if (n1 < 0) {
			if (n2 >= 0 && col2 != NULL)
				show(fp2, argv[1], col2, &line2, &line2len);
			break;
		}
		if (n2 < 0) {
			if (n1 >= 0 && col1 != NULL)
				show(fp1, argv[0], col1, &line1, &line1len);
			break;
		}

		tline2 = NULL;
		if ((tline1 = convert(line1)) != NULL)
			tline2 = convert(line2);
		if (tline1 == NULL || tline2 == NULL)
			comp = strcmp(line1, line2);
		else
			comp = wcscoll(tline1, tline2);
		if (tline1 != NULL)
			free(tline1);
		if (tline2 != NULL)
			free(tline2);

		/* lines are the same */
		if (!comp) {
			read1 = read2 = 1;
			if (col3 != NULL)
				(void)printf("%s%s\n", col3, line1);
			continue;
		}

		/* lines are different */
		if (comp < 0) {
			read1 = 1;
			read2 = 0;
			if (col1 != NULL)
				(void)printf("%s%s\n", col1, line1);
		} else {
			read1 = 0;
			read2 = 1;
			if (col2 != NULL)
				(void)printf("%s%s\n", col2, line2);
		}
	}
	exit(0);
}