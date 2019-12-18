#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wchar_t ;
struct TYPE_2__ {unsigned char* cstr; int /*<<< orphan*/  wstr; } ;
struct bwstring {TYPE_1__ data; } ;

/* Variables and functions */
 int MB_CUR_MAX ; 
 int /*<<< orphan*/  SIZEOF_WCHAR_STRING (size_t) ; 
 struct bwstring* bwsalloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__ const*,int /*<<< orphan*/ ) ; 

struct bwstring *
bwssbdup(const wchar_t *str, size_t len)
{

	if (str == NULL)
		return ((len == 0) ? bwsalloc(0) : NULL);
	else {
		struct bwstring *ret;

		ret = bwsalloc(len);

		if (MB_CUR_MAX == 1)
			for (size_t i = 0; i < len; ++i)
				ret->data.cstr[i] = (unsigned char) str[i];
		else
			memcpy(ret->data.wstr, str, SIZEOF_WCHAR_STRING(len));

		return (ret);
	}
}