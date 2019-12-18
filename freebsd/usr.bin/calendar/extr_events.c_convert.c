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
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 scalar_t__ E2BIG ; 
 scalar_t__ EINVAL ; 
 scalar_t__ conv ; 
 int /*<<< orphan*/ * currentEncoding ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t iconv (scalar_t__,char**,size_t*,char**,size_t*) ; 
 scalar_t__ iconv_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  outputEncoding ; 
 char* realloc (char*,size_t) ; 
 char* strdup (char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static char *
convert(char *input)
{
	char *output;
#ifdef WITH_ICONV
	size_t inleft, outleft, converted = 0;
	char *outbuf, *tmp;
	char *inbuf;
	size_t outlen;

	if (currentEncoding == NULL) {
		output = strdup(input);
		if (output == NULL)
			errx(1, "convert: cannot allocate memory");
		return (output);
	}
	if (conv == (iconv_t)-1) {
		conv = iconv_open(outputEncoding, currentEncoding);
		if (conv == (iconv_t)-1) {
			if (errno == EINVAL)
				errx(1, "Conversion is not supported");
			else
				err(1, "Initialization failure");
		}
	}

	inleft = strlen(input);
	inbuf = input;

	outlen = inleft;
	if ((output = malloc(outlen + 1)) == NULL)
		errx(1, "convert: cannot allocate memory");

	for (;;) {
		errno = 0;
		outbuf = output + converted;
		outleft = outlen - converted;

		converted = iconv(conv, (char **) &inbuf, &inleft, &outbuf, &outleft);
		if (converted != (size_t) -1 || errno == EINVAL) {
			/* finished or invalid multibyte, so truncate and ignore */
			break;
		}

		if (errno != E2BIG) {
			free(output);
			err(1, "convert");
		}

		converted = outbuf - output;
		outlen += inleft * 2;

		if ((tmp = realloc(output, outlen + 1)) == NULL) {
			free(output);
			errx(1, "convert: cannot allocate memory");
		}

		output = tmp;
		outbuf = output + converted;
	}

	/* flush the iconv conversion */
	iconv(conv, NULL, NULL, &outbuf, &outleft);

	/* null terminate the string */
	*outbuf = '\0';
#else
	output = strdup(input);
	if (output == NULL)
		errx(1, "convert: cannot allocate memory");
#endif

	return (output);
}