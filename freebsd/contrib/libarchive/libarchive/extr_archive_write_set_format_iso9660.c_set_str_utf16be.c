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
typedef  int uint16_t ;
struct TYPE_2__ {size_t length; char const* s; } ;
struct iso9660 {TYPE_1__ utf16be; int /*<<< orphan*/  sconv_to_utf16be; } ;
struct archive_write {int /*<<< orphan*/  archive; struct iso9660* format_data; } ;
typedef  enum vdc { ____Placeholder_vdc } vdc ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ ENOMEM ; 
 int VDC_UCS2 ; 
 int /*<<< orphan*/  archive_be16enc (unsigned char*,int) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 scalar_t__ archive_strncpy_l (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  joliet_allowed_char (unsigned char,unsigned char) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,size_t) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int
set_str_utf16be(struct archive_write *a, unsigned char *p, const char *s,
    size_t l, uint16_t uf, enum vdc vdc)
{
	size_t size, i;
	int onepad;

	if (s == NULL)
		s = "";
	if (l & 0x01) {
		onepad = 1;
		l &= ~1;
	} else
		onepad = 0;
	if (vdc == VDC_UCS2) {
		struct iso9660 *iso9660 = a->format_data;
		if (archive_strncpy_l(&iso9660->utf16be, s, strlen(s),
		    iso9660->sconv_to_utf16be) != 0 && errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for UTF-16BE");
			return (ARCHIVE_FATAL);
		}
		size = iso9660->utf16be.length;
		if (size > l)
			size = l;
		memcpy(p, iso9660->utf16be.s, size);
	} else {
		const uint16_t *u16 = (const uint16_t *)s;

		size = 0;
		while (*u16++)
			size += 2;
		if (size > l)
			size = l;
		memcpy(p, s, size);
	}
	for (i = 0; i < size; i += 2, p += 2) {
		if (!joliet_allowed_char(p[0], p[1]))
			archive_be16enc(p, 0x005F);/* '_' */
	}
	l -= size;
	while (l > 0) {
		archive_be16enc(p, uf);
		p += 2;
		l -= 2;
	}
	if (onepad)
		*p = 0;
	return (ARCHIVE_OK);
}