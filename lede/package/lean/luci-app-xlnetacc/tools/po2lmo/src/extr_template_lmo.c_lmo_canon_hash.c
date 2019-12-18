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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  res ;

/* Variables and functions */
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  sfh_hash (char*,int) ; 

uint32_t lmo_canon_hash(const char *str, int len)
{
	char res[4096];
	char *ptr, prev;
	int off;

	if (!str || len >= sizeof(res))
		return 0;

	for (prev = ' ', ptr = res, off = 0; off < len; prev = *str, off++, str++)
	{
		if (isspace(*str))
		{
			if (!isspace(prev))
				*ptr++ = ' ';
		}
		else
		{
			*ptr++ = *str;
		}
	}

	if ((ptr > res) && isspace(*(ptr-1)))
		ptr--;

	return sfh_hash(res, ptr - res);
}