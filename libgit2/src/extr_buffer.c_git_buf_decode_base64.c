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
typedef  int int8_t ;
struct TYPE_4__ {size_t size; char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  ENSURE_SIZE (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int* base64_decode ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

int git_buf_decode_base64(git_buf *buf, const char *base64, size_t len)
{
	size_t i;
	int8_t a, b, c, d;
	size_t orig_size = buf->size, new_size;

	if (len % 4) {
		git_error_set(GIT_ERROR_INVALID, "invalid base64 input");
		return -1;
	}

	assert(len % 4 == 0);
	GIT_ERROR_CHECK_ALLOC_ADD(&new_size, (len / 4 * 3), buf->size);
	GIT_ERROR_CHECK_ALLOC_ADD(&new_size, new_size, 1);
	ENSURE_SIZE(buf, new_size);

	for (i = 0; i < len; i += 4) {
		if ((a = base64_decode[(unsigned char)base64[i]]) < 0 ||
			(b = base64_decode[(unsigned char)base64[i+1]]) < 0 ||
			(c = base64_decode[(unsigned char)base64[i+2]]) < 0 ||
			(d = base64_decode[(unsigned char)base64[i+3]]) < 0) {
			buf->size = orig_size;
			buf->ptr[buf->size] = '\0';

			git_error_set(GIT_ERROR_INVALID, "invalid base64 input");
			return -1;
		}

		buf->ptr[buf->size++] = ((a << 2) | (b & 0x30) >> 4);
		buf->ptr[buf->size++] = ((b & 0x0f) << 4) | ((c & 0x3c) >> 2);
		buf->ptr[buf->size++] = (c & 0x03) << 6 | (d & 0x3f);
	}

	buf->ptr[buf->size] = '\0';
	return 0;
}