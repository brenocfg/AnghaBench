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

/* Variables and functions */
 int ICONV_CONVERTER_CONV (void*,char const**,size_t*,char**,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
iconv_conv(void *handle, const char **inbuf,
	size_t *inbytesleft, char **outbuf, size_t *outbytesleft)
{
	return ICONV_CONVERTER_CONV(handle, inbuf, inbytesleft, outbuf, outbytesleft, 0, 0);
}