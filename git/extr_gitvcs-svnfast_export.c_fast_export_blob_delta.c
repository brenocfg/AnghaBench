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
typedef  scalar_t__ uint32_t ;
struct line_buffer {int dummy; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 scalar_t__ S_IFLNK ; 
 long apply_delta (scalar_t__,struct line_buffer*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buffer_copy_bytes (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  buffer_skip_bytes (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  postimage ; 
 int /*<<< orphan*/  printf (char*,long) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strlen (char*) ; 

void fast_export_blob_delta(uint32_t mode,
				uint32_t old_mode, const char *old_data,
				off_t len, struct line_buffer *input)
{
	long postimage_len;

	assert(len >= 0);
	postimage_len = apply_delta(len, input, old_data, old_mode);
	if (mode == S_IFLNK) {
		buffer_skip_bytes(&postimage, strlen("link "));
		postimage_len -= strlen("link ");
	}
	printf("data %ld\n", postimage_len);
	buffer_copy_bytes(&postimage, postimage_len);
	fputc('\n', stdout);
}