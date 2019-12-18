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
typedef  int /*<<< orphan*/  _key ;

/* Variables and functions */
 unsigned int WT_NONE ; 
 unsigned int WT_RSP ; 
 unsigned int WT_RSRC ; 
 char* _warc_find_eol (char const*,int) ; 
 scalar_t__ memcmp (char const*,char*,unsigned int) ; 
 char* xmemmem (char const*,size_t,char const*,int) ; 

__attribute__((used)) static unsigned int
_warc_rdtyp(const char *buf, size_t bsz)
{
	static const char _key[] = "\r\nWARC-Type:";
	const char *val, *eol;

	if ((val = xmemmem(buf, bsz, _key, sizeof(_key) - 1U)) == NULL) {
		/* no bother */
		return WT_NONE;
	}
	val += sizeof(_key) - 1U;
	if ((eol = _warc_find_eol(val, buf + bsz - val)) == NULL) {
		/* no end of line */
		return WT_NONE;
	}

	/* overread whitespace */
	while (val < eol && (*val == ' ' || *val == '\t'))
		++val;

	if (val + 8U == eol) {
		if (memcmp(val, "resource", 8U) == 0)
			return WT_RSRC;
		else if (memcmp(val, "response", 8U) == 0)
			return WT_RSP;
	}
	return WT_NONE;
}