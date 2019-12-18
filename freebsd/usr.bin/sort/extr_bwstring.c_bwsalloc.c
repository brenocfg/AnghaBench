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
struct TYPE_2__ {char* cstr; int* wstr; } ;
struct bwstring {size_t len; TYPE_1__ data; } ;

/* Variables and functions */
 int MB_CUR_MAX ; 
 int SIZEOF_WCHAR_STRING (size_t) ; 
 struct bwstring* sort_malloc (int) ; 

struct bwstring *
bwsalloc(size_t sz)
{
	struct bwstring *ret;

	if (MB_CUR_MAX == 1)
		ret = sort_malloc(sizeof(struct bwstring) + 1 + sz);
	else
		ret = sort_malloc(sizeof(struct bwstring) +
		    SIZEOF_WCHAR_STRING(sz + 1));
	ret->len = sz;

	if (MB_CUR_MAX == 1)
		ret->data.cstr[ret->len] = '\0';
	else
		ret->data.wstr[ret->len] = L'\0';

	return (ret);
}