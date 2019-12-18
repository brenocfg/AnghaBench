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
struct buf {size_t size; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 struct buf* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct buf*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 

struct buf *
buf_open(size_t len)
{
	struct buf	*buf;

	if ((buf = calloc(1, sizeof(struct buf))) == NULL)
		return (NULL);
	if ((buf->buf = malloc(len)) == NULL) {
		free(buf);
		return (NULL);
	}
	buf->size = len;

	return (buf);
}