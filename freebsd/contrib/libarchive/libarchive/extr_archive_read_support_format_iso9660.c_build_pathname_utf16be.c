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
struct file_info {scalar_t__ utf16be_bytes; int /*<<< orphan*/  utf16be_name; struct file_info* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
build_pathname_utf16be(unsigned char *p, size_t max, size_t *len,
    struct file_info *file)
{
	if (file->parent != NULL && file->parent->utf16be_bytes > 0) {
		if (build_pathname_utf16be(p, max, len, file->parent) != 0)
			return (-1);
		p[*len] = 0;
		p[*len + 1] = '/';
		*len += 2;
	}
	if (file->utf16be_bytes == 0) {
		if (*len + 2 > max)
			return (-1);/* Path is too long! */
		p[*len] = 0;
		p[*len + 1] = '.';
		*len += 2;
	} else {
		if (*len + file->utf16be_bytes > max)
			return (-1);/* Path is too long! */
		memcpy(p + *len, file->utf16be_name, file->utf16be_bytes);
		*len += file->utf16be_bytes;
	}
	return (0);
}