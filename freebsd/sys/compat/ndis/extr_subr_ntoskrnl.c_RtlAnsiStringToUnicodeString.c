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
struct TYPE_5__ {int us_len; int us_maxlen; int /*<<< orphan*/ * us_buf; } ;
typedef  TYPE_1__ unicode_string ;
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int as_len; int /*<<< orphan*/  as_buf; } ;
typedef  TYPE_2__ ansi_string ;

/* Variables and functions */
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ntoskrnl_ascii_to_unicode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

uint32_t
RtlAnsiStringToUnicodeString(unicode_string *dest, ansi_string *src,
	uint8_t allocate)
{
	if (dest == NULL || src == NULL)
		return (STATUS_INVALID_PARAMETER);

	if (allocate == TRUE) {
		dest->us_buf = ExAllocatePoolWithTag(NonPagedPool,
		    src->as_len * 2, 0);
		if (dest->us_buf == NULL)
			return (STATUS_INSUFFICIENT_RESOURCES);
		dest->us_len = dest->us_maxlen = strlen(src->as_buf) * 2;
	} else {
		dest->us_len = src->as_len * 2; /* XXX */
		if (dest->us_maxlen < dest->us_len)
			dest->us_len = dest->us_maxlen;
	}

	ntoskrnl_ascii_to_unicode(src->as_buf, dest->us_buf,
	    dest->us_len / 2);

	return (STATUS_SUCCESS);
}