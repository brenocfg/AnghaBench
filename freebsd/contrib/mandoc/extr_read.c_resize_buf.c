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
struct buf {int sz; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  mandoc_realloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
resize_buf(struct buf *buf, size_t initial)
{

	buf->sz = buf->sz > initial/2 ? 2 * buf->sz : initial;
	buf->buf = mandoc_realloc(buf->buf, buf->sz);
}