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
struct archive_write {int dummy; } ;
typedef  enum vdc { ____Placeholder_vdc } vdc ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
#define  VDC_LOWERCASE 131 
#define  VDC_STD 130 
#define  VDC_UCS2 129 
#define  VDC_UCS2_DIRECT 128 
 int /*<<< orphan*/  d1_characters_map ; 
 int /*<<< orphan*/  d_characters_map ; 
 int /*<<< orphan*/  set_str (unsigned char*,char const*,int,int,int /*<<< orphan*/ ) ; 
 int set_str_utf16be (struct archive_write*,unsigned char*,char const*,int,int,int) ; 

__attribute__((used)) static int
set_str_d_characters_bp(struct archive_write *a, unsigned char *bp,
    int from, int to, const char *s, enum  vdc vdc)
{
	int r;

	switch (vdc) {
	case VDC_STD:
		set_str(bp+from, s, to - from + 1, 0x20,
		    d_characters_map);
		r = ARCHIVE_OK;
		break;
	case VDC_LOWERCASE:
		set_str(bp+from, s, to - from + 1, 0x20,
		    d1_characters_map);
		r = ARCHIVE_OK;
		break;
	case VDC_UCS2:
	case VDC_UCS2_DIRECT:
		r = set_str_utf16be(a, bp+from, s, to - from + 1,
		    0x0020, vdc);
		break;
	default:
		r = ARCHIVE_FATAL;
	}
	return (r);
}