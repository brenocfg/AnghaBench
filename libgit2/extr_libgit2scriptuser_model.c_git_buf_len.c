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
struct git_buf {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int strlen (int /*<<< orphan*/ ) ; 

int git_buf_len(const struct git_buf *buf)
{
	return strlen(buf->ptr);
}