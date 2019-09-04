#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t count; char** strings; } ;
typedef  TYPE_1__ git_strarray ;
struct TYPE_9__ {char* ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  git_buf_clear (TYPE_2__*) ; 
 scalar_t__ git_buf_sets (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  git_buf_truncate (TYPE_2__*,int) ; 

int git_buf_text_common_prefix(git_buf *buf, const git_strarray *strings)
{
	size_t i;
	const char *str, *pfx;

	git_buf_clear(buf);

	if (!strings || !strings->count)
		return 0;

	/* initialize common prefix to first string */
	if (git_buf_sets(buf, strings->strings[0]) < 0)
		return -1;

	/* go through the rest of the strings, truncating to shared prefix */
	for (i = 1; i < strings->count; ++i) {

		for (str = strings->strings[i], pfx = buf->ptr;
			 *str && *str == *pfx; str++, pfx++)
			/* scanning */;

		git_buf_truncate(buf, pfx - buf->ptr);

		if (!buf->size)
			break;
	}

	return 0;
}