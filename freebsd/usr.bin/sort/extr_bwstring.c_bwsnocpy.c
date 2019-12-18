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
struct TYPE_2__ {char* wstr; char* cstr; } ;
struct bwstring {size_t len; TYPE_1__ data; } ;

/* Variables and functions */
 int MB_CUR_MAX ; 
 size_t SIZEOF_WCHAR_STRING (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

struct bwstring *
bwsnocpy(struct bwstring *dst, const struct bwstring *src, size_t offset,
    size_t size)
{

	if (offset >= src->len) {
		dst->data.wstr[0] = 0;
		dst->len = 0;
	} else {
		size_t nums = src->len - offset;

		if (nums > dst->len)
			nums = dst->len;
		if (nums > size)
			nums = size;
		dst->len = nums;
		if (MB_CUR_MAX == 1) {
			memcpy(dst->data.cstr, src->data.cstr + offset,
			    (nums));
			dst->data.cstr[dst->len] = '\0';
		} else {
			memcpy(dst->data.wstr, src->data.wstr + offset,
			    SIZEOF_WCHAR_STRING(nums));
			dst->data.wstr[dst->len] = L'\0';
		}
	}
	return (dst);
}