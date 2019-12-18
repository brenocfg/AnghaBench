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
struct ringbuf_entry {scalar_t__ len; } ;
struct ringbuf {int fill; int len; int slen; struct ringbuf_entry* buf; } ;

/* Variables and functions */

struct ringbuf_entry * ringbuf_get(struct ringbuf *r, int i)
{
	struct ringbuf_entry *e = r->buf + (((r->fill + i) % r->len) * r->slen);

	if (e->len > 0)
		return e;

	return NULL;
}