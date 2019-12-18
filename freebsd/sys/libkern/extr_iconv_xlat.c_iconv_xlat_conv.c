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
typedef  size_t u_char ;
struct iconv_xlat {int /*<<< orphan*/ * d_table; } ;

/* Variables and functions */
 int min (size_t,size_t) ; 

__attribute__((used)) static int
iconv_xlat_conv(void *d2p, const char **inbuf,
	size_t *inbytesleft, char **outbuf, size_t *outbytesleft,
	int convchar, int casetype)
{
	struct iconv_xlat *dp = (struct iconv_xlat*)d2p;
	const char *src;
	char *dst;
	int n, r;

	if (inbuf == NULL || *inbuf == NULL || outbuf == NULL || *outbuf == NULL)
		return 0;
	if (casetype != 0)
		return -1;
	if (convchar == 1)
		r = n = 1;
	else
		r = n = min(*inbytesleft, *outbytesleft);
	src = *inbuf;
	dst = *outbuf;
	while(r--)
		*dst++ = dp->d_table[(u_char)*src++];
	*inbuf += n;
	*outbuf += n;
	*inbytesleft -= n;
	*outbytesleft -= n;
	return 0;
}