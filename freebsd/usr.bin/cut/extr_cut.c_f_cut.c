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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 scalar_t__ autostop ; 
 char* dcharmb ; 
 int /*<<< orphan*/  err (int,char*) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (char*,size_t,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_delim (char) ; 
 char* malloc (size_t) ; 
 int maxval ; 
 size_t mbrtowc (char*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* positions ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  sflag ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warnc (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ wflag ; 

__attribute__((used)) static int
f_cut(FILE *fp, const char *fname)
{
	wchar_t ch;
	int field, i, isdelim;
	char *pos, *p;
	int output;
	char *lbuf, *mlbuf;
	size_t clen, lbuflen, reallen;

	mlbuf = NULL;
	while ((lbuf = fgetln(fp, &lbuflen)) != NULL) {
		reallen = lbuflen;
		/* Assert EOL has a newline. */
		if (*(lbuf + lbuflen - 1) != '\n') {
			/* Can't have > 1 line with no trailing newline. */
			mlbuf = malloc(lbuflen + 1);
			if (mlbuf == NULL)
				err(1, "malloc");
			memcpy(mlbuf, lbuf, lbuflen);
			*(mlbuf + lbuflen) = '\n';
			lbuf = mlbuf;
			reallen++;
		}
		output = 0;
		for (isdelim = 0, p = lbuf;; p += clen) {
			clen = mbrtowc(&ch, p, lbuf + reallen - p, NULL);
			if (clen == (size_t)-1 || clen == (size_t)-2) {
				warnc(EILSEQ, "%s", fname);
				free(mlbuf);
				return (1);
			}
			if (clen == 0)
				clen = 1;
			/* this should work if newline is delimiter */
			if (is_delim(ch))
				isdelim = 1;
			if (ch == '\n') {
				if (!isdelim && !sflag)
					(void)fwrite(lbuf, lbuflen, 1, stdout);
				break;
			}
		}
		if (!isdelim)
			continue;

		pos = positions + 1;
		for (field = maxval, p = lbuf; field; --field, ++pos) {
			if (*pos && output++)
				for (i = 0; dcharmb[i] != '\0'; i++)
					putchar(dcharmb[i]);
			for (;;) {
				clen = mbrtowc(&ch, p, lbuf + reallen - p,
				    NULL);
				if (clen == (size_t)-1 || clen == (size_t)-2) {
					warnc(EILSEQ, "%s", fname);
					free(mlbuf);
					return (1);
				}
				if (clen == 0)
					clen = 1;
				p += clen;
				if (ch == '\n' || is_delim(ch)) {
					/* compress whitespace */
					if (wflag && ch != '\n')
						while (is_delim(*p))
							p++;
					break;
				}
				if (*pos)
					for (i = 0; i < (int)clen; i++)
						putchar(p[i - clen]);
			}
			if (ch == '\n')
				break;
		}
		if (ch != '\n') {
			if (autostop) {
				if (output)
					for (i = 0; dcharmb[i] != '\0'; i++)
						putchar(dcharmb[i]);
				for (; (ch = *p) != '\n'; ++p)
					(void)putchar(ch);
			} else
				for (; (ch = *p) != '\n'; ++p);
		}
		(void)putchar('\n');
	}
	free(mlbuf);
	return (0);
}