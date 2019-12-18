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

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int iconv (int /*<<< orphan*/ ,char const**,size_t*,char**,size_t*) ; 
 int /*<<< orphan*/  iconv_open (char*,char*) ; 
 char* malloc (size_t) ; 
 size_t strlen (char*) ; 

int
main(void)
{
	iconv_t cd;
	size_t inbytes, outbytes;
	char *str1 = "FOOBAR";
	const char *str2 = "FOOBAR";
	char ** in1;
	const char ** in2 = &str2;
	char *out1, *out2;

	inbytes = outbytes = strlen("FOOBAR");

	if ((cd = iconv_open("UTF-8", "ASCII")) == (iconv_t)-1)
		err(1, NULL);

	if ((out2 = malloc(inbytes)) == NULL)
		err(1, NULL);

	if (iconv(cd, in2, &inbytes, &out2, &outbytes) == -1)
		err(1, NULL);

	in1 = &str1;
	inbytes = outbytes = strlen("FOOBAR");

	if ((out1 = malloc(inbytes)) == NULL)
		err(1, NULL);

	if (iconv(cd, in1, &inbytes, &out1, &outbytes) == -1)
		err(1, NULL);

	return (EXIT_SUCCESS);

}