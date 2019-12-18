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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  _ISO2022State ;
typedef  int /*<<< orphan*/  _ISO2022EncodingInfo ;

/* Variables and functions */
 int E2BIG ; 
 int MB_LEN_MAX ; 
 int _ISO2022_sputwchar (int /*<<< orphan*/ *,int,char*,int,char**,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

__attribute__((used)) static int
_citrus_ISO2022_put_state_reset(_ISO2022EncodingInfo * __restrict ei,
    char * __restrict s, size_t n, _ISO2022State * __restrict psenc,
    size_t * __restrict nresult)
{
	char *result;
	char buf[MB_LEN_MAX];
	size_t len;
	int ret;

	/* XXX state will be modified after this operation... */
	ret = _ISO2022_sputwchar(ei, L'\0', buf, sizeof(buf), &result, psenc,
	    &len);
	if (ret) {
		*nresult = len;
		return (ret);
	}

	if (sizeof(buf) < len || n < len-1) {
		/* XXX should recover state? */
		*nresult = (size_t)-1;
		return (E2BIG);
	}

	memcpy(s, buf, len - 1);
	*nresult = len - 1;
	return (0);
}