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
struct iconv_hooks {int /*<<< orphan*/ * uc_hook; int /*<<< orphan*/  wc_hook; } ;
typedef  int /*<<< orphan*/  s ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  ICONV_SET_HOOKS ; 
 size_t iconv (scalar_t__,char const**,size_t*,char**,size_t*) ; 
 int iconv_close (scalar_t__) ; 
 scalar_t__ iconv_open (char*,char*) ; 
 scalar_t__ iconvctl (scalar_t__,int /*<<< orphan*/ ,void*) ; 
 char* malloc (int) ; 
 scalar_t__ wc_hook ; 
 int /*<<< orphan*/  wchar_hook ; 

__attribute__((used)) static int
ctl_wc_hook(void)
{
	struct iconv_hooks hooks;
	iconv_t cd;
	size_t inbytesleft, outbytesleft = 40;
	const char **inptr;
	const char *s = "Hello World!";
	char **outptr;
	char *outbuf;

	inptr = &s;
	hooks.wc_hook = wchar_hook;
	hooks.uc_hook = NULL;

	outbuf = malloc(40);
	outptr = &outbuf;
	inbytesleft = sizeof(s);

	cd = iconv_open("SHIFT_JIS", "ASCII");
	if (cd == (iconv_t)-1)
		return (-1);
	if (iconvctl(cd, ICONV_SET_HOOKS, (void *)&hooks) != 0)
		return (-1);
	if (iconv(cd, inptr, &inbytesleft, outptr, &outbytesleft) == (size_t)-1)
		return (-1);
	if (iconv_close(cd) == -1)
		return (-1);
	return (wc_hook ? 0 : 1);
}