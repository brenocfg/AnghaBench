#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t size; int* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  ENSURE_SIZE (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int HEX_DECODE (char const) ; 
 scalar_t__ isxdigit (char const) ; 

int git_buf_decode_percent(
	git_buf *buf,
	const char *str,
	size_t str_len)
{
	size_t str_pos, new_size;

	GIT_ERROR_CHECK_ALLOC_ADD(&new_size, buf->size, str_len);
	GIT_ERROR_CHECK_ALLOC_ADD(&new_size, new_size, 1);
	ENSURE_SIZE(buf, new_size);

	for (str_pos = 0; str_pos < str_len; buf->size++, str_pos++) {
		if (str[str_pos] == '%' &&
			str_len > str_pos + 2 &&
			isxdigit(str[str_pos + 1]) &&
			isxdigit(str[str_pos + 2])) {
			buf->ptr[buf->size] = (HEX_DECODE(str[str_pos + 1]) << 4) +
				HEX_DECODE(str[str_pos + 2]);
			str_pos += 2;
		} else {
			buf->ptr[buf->size] = str[str_pos];
		}
	}

	buf->ptr[buf->size] = '\0';
	return 0;
}