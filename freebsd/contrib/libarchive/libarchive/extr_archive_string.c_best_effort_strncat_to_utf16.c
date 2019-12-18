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
struct archive_string_conv {int dummy; } ;
struct archive_string {size_t length; char* s; } ;

/* Variables and functions */
 unsigned int UNICODE_R_CHAR ; 
 int /*<<< orphan*/  archive_be16enc (char*,unsigned int) ; 
 int /*<<< orphan*/  archive_le16enc (char*,unsigned int) ; 
 int /*<<< orphan*/ * archive_string_ensure (struct archive_string*,size_t) ; 

__attribute__((used)) static int
best_effort_strncat_to_utf16(struct archive_string *as16, const void *_p,
    size_t length, struct archive_string_conv *sc, int bigendian)
{
	const char *s = (const char *)_p;
	char *utf16;
	size_t remaining;
	int ret;

	(void)sc; /* UNUSED */
	/*
	 * Other case, we should do the best effort.
	 * If all character are ASCII(<0x7f), we can convert it.
	 * if not , we set a alternative character and return -1.
	 */
	ret = 0;
	remaining = length;

	if (archive_string_ensure(as16,
	    as16->length + (length + 1) * 2) == NULL)
		return (-1);

	utf16 = as16->s + as16->length;
	while (remaining--) {
		unsigned c = *s++;
		if (c > 127) {
			/* We cannot handle it. */
			c = UNICODE_R_CHAR;
			ret = -1;
		}
		if (bigendian)
			archive_be16enc(utf16, c);
		else
			archive_le16enc(utf16, c);
		utf16 += 2;
	}
	as16->length = utf16 - as16->s;
	as16->s[as16->length] = 0;
	as16->s[as16->length+1] = 0;
	return (ret);
}