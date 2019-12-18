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
typedef  int /*<<< orphan*/  iconv_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ E2BIG ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  ICONV_SET_DISCARD_ILSEQ ; 
 int INBUFSIZE ; 
 int OUTBUFSIZE ; 
 size_t __iconv (int /*<<< orphan*/ ,char**,size_t*,char**,size_t*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 size_t iconv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,size_t*) ; 
 int iconvctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warnx (char*,unsigned long long) ; 

__attribute__((used)) static int
do_conv(FILE *fp, iconv_t cd, bool silent, bool hide_invalid)
{
	char inbuf[INBUFSIZE], outbuf[OUTBUFSIZE], *in, *out;
	unsigned long long invalids;
	size_t inbytes, outbytes, ret;

	int arg = (int)hide_invalid;
	if (iconvctl(cd, ICONV_SET_DISCARD_ILSEQ, (void *)&arg) == -1)
		err(EXIT_FAILURE, "iconvctl(DISCARD_ILSEQ, %d)", arg);

	invalids = 0;
	while ((inbytes = fread(inbuf, 1, INBUFSIZE, fp)) > 0) {
		in = inbuf;
		while (inbytes > 0) {
			size_t inval;

			out = outbuf;
			outbytes = OUTBUFSIZE;
			ret = __iconv(cd, &in, &inbytes, &out, &outbytes,
			    0, &inval);
			invalids += inval;
			if (outbytes < OUTBUFSIZE)
				(void)fwrite(outbuf, 1, OUTBUFSIZE - outbytes,
				    stdout);
			if (ret == (size_t)-1 && errno != E2BIG) {
				if (errno != EINVAL || in == inbuf)
					err(EXIT_FAILURE, "iconv()");

				/* incomplete input character */
				(void)memmove(inbuf, in, inbytes);
				ret = fread(inbuf + inbytes, 1,
				    INBUFSIZE - inbytes, fp);
				if (ret == 0) {
					fflush(stdout);
					if (feof(fp))
						errx(EXIT_FAILURE,
						    "unexpected end of file; "
						    "the last character is "
						    "incomplete.");
					else
						err(EXIT_FAILURE, "fread()");
				}
				in = inbuf;
				inbytes += ret;
			}
		}
	}
	/* reset the shift state of the output buffer */
	outbytes = OUTBUFSIZE;
	out = outbuf;
	ret = iconv(cd, NULL, NULL, &out, &outbytes);
	if (ret == (size_t)-1)
		err(EXIT_FAILURE, "iconv()");
	if (outbytes < OUTBUFSIZE)
		(void)fwrite(outbuf, 1, OUTBUFSIZE - outbytes, stdout);

	if (invalids > 0 && !silent)
		warnx("warning: invalid characters: %llu", invalids);

	return (invalids > 0);
}