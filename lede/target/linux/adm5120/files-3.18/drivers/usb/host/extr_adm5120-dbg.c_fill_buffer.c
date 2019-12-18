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
struct debug_buffer {char* page; int (* fill_func ) (struct debug_buffer*) ;int count; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int stub1 (struct debug_buffer*) ; 

__attribute__((used)) static int fill_buffer(struct debug_buffer *buf)
{
	int ret = 0;

	if (!buf->page)
		buf->page = (char *)get_zeroed_page(GFP_KERNEL);

	if (!buf->page) {
		ret = -ENOMEM;
		goto out;
	}

	ret = buf->fill_func(buf);

	if (ret >= 0) {
		buf->count = ret;
		ret = 0;
	}

out:
	return ret;
}