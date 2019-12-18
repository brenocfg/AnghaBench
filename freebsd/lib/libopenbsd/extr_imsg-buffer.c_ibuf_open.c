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
struct ibuf {size_t size; size_t max; int fd; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 struct ibuf* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct ibuf*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 

struct ibuf *
ibuf_open(size_t len)
{
	struct ibuf	*buf;

	if ((buf = calloc(1, sizeof(struct ibuf))) == NULL)
		return (NULL);
	if ((buf->buf = malloc(len)) == NULL) {
		free(buf);
		return (NULL);
	}
	buf->size = buf->max = len;
	buf->fd = -1;

	return (buf);
}