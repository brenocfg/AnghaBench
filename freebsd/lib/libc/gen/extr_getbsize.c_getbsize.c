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
typedef  int /*<<< orphan*/  header ;

/* Variables and functions */
 long GB ; 
 long KB ; 
 long MAXB ; 
 long MB ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,long,char const*) ; 
 int strlen (char*) ; 
 long strtol (char*,char**,int) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

char *
getbsize(int *headerlenp, long *blocksizep)
{
	static char header[20];
	long n, max, mul, blocksize;
	char *ep, *p;
	const char *form;

#define	KB	(1024L)
#define	MB	(1024L * 1024L)
#define	GB	(1024L * 1024L * 1024L)
#define	MAXB	GB		/* No tera, peta, nor exa. */
	form = "";
	if ((p = getenv("BLOCKSIZE")) != NULL && *p != '\0') {
		if ((n = strtol(p, &ep, 10)) < 0)
			goto underflow;
		if (n == 0)
			n = 1;
		if (*ep && ep[1])
			goto fmterr;
		switch (*ep) {
		case 'G': case 'g':
			form = "G";
			max = MAXB / GB;
			mul = GB;
			break;
		case 'K': case 'k':
			form = "K";
			max = MAXB / KB;
			mul = KB;
			break;
		case 'M': case 'm':
			form = "M";
			max = MAXB / MB;
			mul = MB;
			break;
		case '\0':
			max = MAXB;
			mul = 1;
			break;
		default:
fmterr:			warnx("%s: unknown blocksize", p);
			n = 512;
			max = MAXB;
			mul = 1;
			break;
		}
		if (n > max) {
			warnx("maximum blocksize is %ldG", MAXB / GB);
			n = max;
		}
		if ((blocksize = n * mul) < 512) {
underflow:		warnx("minimum blocksize is 512");
			form = "";
			blocksize = n = 512;
		}
	} else
		blocksize = n = 512;

	(void)snprintf(header, sizeof(header), "%ld%s-blocks", n, form);
	*headerlenp = strlen(header);
	*blocksizep = blocksize;
	return (header);
}