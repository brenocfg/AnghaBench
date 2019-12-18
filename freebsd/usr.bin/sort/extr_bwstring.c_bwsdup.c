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
struct TYPE_2__ {int /*<<< orphan*/  wstr; int /*<<< orphan*/  cstr; } ;
struct bwstring {int /*<<< orphan*/  len; TYPE_1__ data; } ;

/* Variables and functions */
 int MB_CUR_MAX ; 
 int /*<<< orphan*/  SIZEOF_WCHAR_STRING (int /*<<< orphan*/ ) ; 
 struct bwstring* bwsalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct bwstring *
bwsdup(const struct bwstring *s)
{

	if (s == NULL)
		return (NULL);
	else {
		struct bwstring *ret = bwsalloc(s->len);

		if (MB_CUR_MAX == 1)
			memcpy(ret->data.cstr, s->data.cstr, (s->len));
		else
			memcpy(ret->data.wstr, s->data.wstr,
			    SIZEOF_WCHAR_STRING(s->len));

		return (ret);
	}
}