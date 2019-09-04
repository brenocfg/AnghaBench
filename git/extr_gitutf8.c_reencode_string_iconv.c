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
typedef  scalar_t__ iconv_ibp ;

/* Variables and functions */
 scalar_t__ E2BIG ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t iconv (int /*<<< orphan*/ ,scalar_t__*,size_t*,char**,size_t*) ; 
 size_t st_add (size_t,int) ; 
 size_t st_add3 (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  st_mult (size_t,int) ; 
 char* xmalloc (size_t) ; 
 char* xrealloc (char*,size_t) ; 

char *reencode_string_iconv(const char *in, size_t insz, iconv_t conv,
			    size_t bom_len, size_t *outsz_p)
{
	size_t outsz, outalloc;
	char *out, *outpos;
	iconv_ibp cp;

	outsz = insz;
	outalloc = st_add(outsz, 1 + bom_len); /* for terminating NUL */
	out = xmalloc(outalloc);
	outpos = out + bom_len;
	cp = (iconv_ibp)in;

	while (1) {
		size_t cnt = iconv(conv, &cp, &insz, &outpos, &outsz);

		if (cnt == (size_t) -1) {
			size_t sofar;
			if (errno != E2BIG) {
				free(out);
				return NULL;
			}
			/* insz has remaining number of bytes.
			 * since we started outsz the same as insz,
			 * it is likely that insz is not enough for
			 * converting the rest.
			 */
			sofar = outpos - out;
			outalloc = st_add3(sofar, st_mult(insz, 2), 32);
			out = xrealloc(out, outalloc);
			outpos = out + sofar;
			outsz = outalloc - sofar - 1;
		}
		else {
			*outpos = '\0';
			if (outsz_p)
				*outsz_p = outpos - out;
			break;
		}
	}
	return out;
}