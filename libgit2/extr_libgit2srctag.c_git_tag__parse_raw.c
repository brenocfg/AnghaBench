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

/* Variables and functions */
 int tag_parse (void*,char const*,char const*) ; 

int git_tag__parse_raw(void *_tag, const char *data, size_t size)
{
	return tag_parse(_tag, data, data + size);
}