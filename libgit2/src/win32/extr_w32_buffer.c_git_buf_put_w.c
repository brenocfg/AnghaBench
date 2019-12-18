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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_4__ {size_t size; char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  WC_ERR_INVALID_CHARS ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ git_buf_grow (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  git_error_set_oom () ; 
 int handle_wc_error () ; 

int git_buf_put_w(git_buf *buf, const wchar_t *string_w, size_t len_w)
{
	int utf8_len, utf8_write_len;
	size_t new_size;

	if (!len_w) {
		return 0;
	} else if (len_w > INT_MAX) {
		git_error_set_oom();
		return -1;
	}

	assert(string_w);

	/* Measure the string necessary for conversion */
	if ((utf8_len = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, string_w, (int)len_w, NULL, 0, NULL, NULL)) == 0)
		return 0;

	assert(utf8_len > 0);

	GIT_ERROR_CHECK_ALLOC_ADD(&new_size, buf->size, (size_t)utf8_len);
	GIT_ERROR_CHECK_ALLOC_ADD(&new_size, new_size, 1);

	if (git_buf_grow(buf, new_size) < 0)
		return -1;

	if ((utf8_write_len = WideCharToMultiByte(
			CP_UTF8, WC_ERR_INVALID_CHARS, string_w, (int)len_w, &buf->ptr[buf->size], utf8_len, NULL, NULL)) == 0)
		return handle_wc_error();

	assert(utf8_write_len == utf8_len);

	buf->size += utf8_write_len;
	buf->ptr[buf->size] = '\0';
	return 0;
}