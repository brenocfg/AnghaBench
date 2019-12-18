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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  iconv_t ;

/* Variables and functions */
 int iconv (int /*<<< orphan*/ ,char const**,size_t*,char**,size_t*) ; 
 int /*<<< orphan*/  iconv_open (char*,char*) ; 

__attribute__((used)) static int
conv_ret(void)
{
	iconv_t cd;
	size_t inbytesleft, outbytesleft;
	const char *inptr;
	char *outptr;
	uint32_t outbuf[4];
	uint32_t inbuf[2] = { 0x00000151, 0x00000171 };

	if ((cd = iconv_open("ASCII", "UTF-32LE")) == (iconv_t)-1)
		return (1);

	inptr = (const char *)inbuf;
	outptr = (char *)outbuf;
	inbytesleft = 8;
	outbytesleft = 16;

	return (iconv(cd, &inptr, &inbytesleft, &outptr, &outbytesleft) == 2 ? 0 : 1);
}