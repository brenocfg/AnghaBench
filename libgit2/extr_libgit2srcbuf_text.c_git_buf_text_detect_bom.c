#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; char* ptr; } ;
typedef  TYPE_1__ git_buf ;
typedef  int /*<<< orphan*/  git_bom_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BOM_NONE ; 
 int /*<<< orphan*/  GIT_BOM_UTF16_BE ; 
 int /*<<< orphan*/  GIT_BOM_UTF16_LE ; 
 int /*<<< orphan*/  GIT_BOM_UTF32_BE ; 
 int /*<<< orphan*/  GIT_BOM_UTF32_LE ; 
 int /*<<< orphan*/  GIT_BOM_UTF8 ; 

int git_buf_text_detect_bom(git_bom_t *bom, const git_buf *buf)
{
	const char *ptr;
	size_t len;

	*bom = GIT_BOM_NONE;
	/* need at least 2 bytes to look for any BOM */
	if (buf->size < 2)
		return 0;

	ptr = buf->ptr;
	len = buf->size;

	switch (*ptr++) {
	case 0:
		if (len >= 4 && ptr[0] == 0 && ptr[1] == '\xFE' && ptr[2] == '\xFF') {
			*bom = GIT_BOM_UTF32_BE;
			return 4;
		}
		break;
	case '\xEF':
		if (len >= 3 && ptr[0] == '\xBB' && ptr[1] == '\xBF') {
			*bom = GIT_BOM_UTF8;
			return 3;
		}
		break;
	case '\xFE':
		if (*ptr == '\xFF') {
			*bom = GIT_BOM_UTF16_BE;
			return 2;
		}
		break;
	case '\xFF':
		if (*ptr != '\xFE')
			break;
		if (len >= 4 && ptr[1] == 0 && ptr[2] == 0) {
			*bom = GIT_BOM_UTF32_LE;
			return 4;
		} else {
			*bom = GIT_BOM_UTF16_LE;
			return 2;
		}
		break;
	default:
		break;
	}

	return 0;
}