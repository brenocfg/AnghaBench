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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  iconv_t ;

/* Variables and functions */
 int EINVAL ; 
 int errno ; 
 int iconv (int /*<<< orphan*/ ,char const**,size_t*,char**,size_t*) ; 
 int /*<<< orphan*/  iconv_open (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
conv_einval(void)
{
	iconv_t	 cd;
	size_t inbytesleft, outbytesleft;
	const char *inptr;
	char *outptr;
	uint32_t outbuf[4];
        uint16_t inbuf[1] = { 0xEA42 };
	int ret;

	if ((cd = iconv_open("UTF-32", "BIG5")) == (iconv_t)-1)
		return (1);

	inptr = (const char *)inbuf;
	outptr = (char *)outbuf;
	inbytesleft = 2;
	outbytesleft = 16;

	errno = 0;
	ret = iconv(cd, &inptr, &inbytesleft, &outptr, &outbytesleft);

#ifdef VERBOSE
	printf("inptr - inbuf = %d\n", (const uint8_t *)inptr - (uint8_t *)inbuf);
	printf("inbytesleft = %d\n", inbytesleft);
	printf("outbytesleft = %d\n", outbytesleft);
	printf("outptr - outbuf = %d\n", (uint8_t *)outptr - (uint8_t *)outbuf);
	printf("errno = %d\n", errno);
	printf("ret = %d\n", (int)ret);
#endif

	if (((const uint8_t *)inptr - (uint8_t *)inbuf == 1) && (inbytesleft == 1)  &&
	    (outbytesleft == 8) && ((uint8_t *)outptr - (uint8_t *)outbuf == 8) &&
	    (errno == EINVAL) && ((size_t)ret == (size_t)-1))
		return (0);
	else
		return (1);
}