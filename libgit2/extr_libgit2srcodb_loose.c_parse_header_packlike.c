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
struct TYPE_3__ {unsigned long type; size_t size; } ;
typedef  TYPE_1__ obj_hdr ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OBJECT ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int parse_header_packlike(
	obj_hdr *out, size_t *out_len, const unsigned char *data, size_t len)
{
	unsigned long c;
	size_t shift, size, used = 0;

	if (len == 0)
		goto on_error;

	c = data[used++];
	out->type = (c >> 4) & 7;

	size = c & 15;
	shift = 4;
	while (c & 0x80) {
		if (len <= used)
			goto on_error;

		if (sizeof(size_t) * 8 <= shift)
			goto on_error;

		c = data[used++];
		size += (c & 0x7f) << shift;
		shift += 7;
	}

	out->size = size;

	if (out_len)
		*out_len = used;

	return 0;

on_error:
	git_error_set(GIT_ERROR_OBJECT, "failed to parse loose object: invalid header");
	return -1;
}