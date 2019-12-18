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
struct netbuf {scalar_t__ len; scalar_t__ maxlen; int /*<<< orphan*/ * buf; } ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static bool_t
netbuf_copybuf(struct netbuf *dst, const struct netbuf *src)
{
	assert(src->len <= src->maxlen);

	if (dst->maxlen < src->len || dst->buf == NULL) {
		free(dst->buf);
		if ((dst->buf = calloc(1, src->maxlen)) == NULL)
			return (FALSE);
		dst->maxlen = src->maxlen;
	}

	dst->len = src->len;
	memcpy(dst->buf, src->buf, src->len);

	return (TRUE);
}