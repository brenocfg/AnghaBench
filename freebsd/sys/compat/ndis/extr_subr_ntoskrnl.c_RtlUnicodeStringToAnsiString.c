#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int us_len; int /*<<< orphan*/  us_buf; } ;
typedef  TYPE_1__ unicode_string ;
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int as_len; int as_maxlen; int /*<<< orphan*/ * as_buf; } ;
typedef  TYPE_2__ ansi_string ;

/* Variables and functions */
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ntoskrnl_unicode_to_ascii (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

uint32_t
RtlUnicodeStringToAnsiString(ansi_string *dest, unicode_string *src, uint8_t allocate)
{
	if (dest == NULL || src == NULL)
		return (STATUS_INVALID_PARAMETER);

	dest->as_len = src->us_len / 2;
	if (dest->as_maxlen < dest->as_len)
		dest->as_len = dest->as_maxlen;

	if (allocate == TRUE) {
		dest->as_buf = ExAllocatePoolWithTag(NonPagedPool,
		    (src->us_len / 2) + 1, 0);
		if (dest->as_buf == NULL)
			return (STATUS_INSUFFICIENT_RESOURCES);
		dest->as_len = dest->as_maxlen = src->us_len / 2;
	} else {
		dest->as_len = src->us_len / 2; /* XXX */
		if (dest->as_maxlen < dest->as_len)
			dest->as_len = dest->as_maxlen;
	}

	ntoskrnl_unicode_to_ascii(src->us_buf, dest->as_buf,
	    dest->as_len * 2);

	return (STATUS_SUCCESS);
}