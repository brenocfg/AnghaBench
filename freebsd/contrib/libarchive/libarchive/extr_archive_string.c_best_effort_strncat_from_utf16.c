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
typedef  int uint32_t ;
struct archive_string_conv {int dummy; } ;
struct archive_string {size_t length; char* s; } ;

/* Variables and functions */
 int /*<<< orphan*/ * archive_string_ensure (struct archive_string*,size_t) ; 
 int utf16_to_unicode (int*,char const*,size_t,int) ; 

__attribute__((used)) static int
best_effort_strncat_from_utf16(struct archive_string *as, const void *_p,
    size_t bytes, struct archive_string_conv *sc, int be)
{
	const char *utf16 = (const char *)_p;
	char *mbs;
	uint32_t uc;
	int n, ret;

	(void)sc; /* UNUSED */
	/*
	 * Other case, we should do the best effort.
	 * If all character are ASCII(<0x7f), we can convert it.
	 * if not , we set a alternative character and return -1.
	 */
	ret = 0;
	if (archive_string_ensure(as, as->length + bytes +1) == NULL)
		return (-1);
	mbs = as->s + as->length;

	while ((n = utf16_to_unicode(&uc, utf16, bytes, be)) != 0) {
		if (n < 0) {
			n *= -1;
			ret =  -1;
		}
		bytes -= n;
		utf16 += n;

		if (uc > 127) {
			/* We cannot handle it. */
			*mbs++ = '?';
			ret =  -1;
		} else
			*mbs++ = (char)uc;
	}
	as->length = mbs - as->s;
	as->s[as->length] = '\0';
	return (ret);
}