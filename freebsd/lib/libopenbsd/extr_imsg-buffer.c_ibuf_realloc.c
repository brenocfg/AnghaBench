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
typedef  int /*<<< orphan*/  u_char ;
struct ibuf {scalar_t__ wpos; scalar_t__ max; scalar_t__ size; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,scalar_t__) ; 

int
ibuf_realloc(struct ibuf *buf, size_t len)
{
	u_char	*b;

	/* on static buffers max is eq size and so the following fails */
	if (buf->wpos + len > buf->max) {
		errno = ERANGE;
		return (-1);
	}

	b = realloc(buf->buf, buf->wpos + len);
	if (b == NULL)
		return (-1);
	buf->buf = b;
	buf->size = buf->wpos + len;

	return (0);
}