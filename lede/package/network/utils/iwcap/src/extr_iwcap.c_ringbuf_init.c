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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ringbuf_entry {int dummy; } ;
struct ringbuf {int len; int slen; scalar_t__ buf; scalar_t__ fill; } ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

struct ringbuf * ringbuf_init(uint32_t num_item, uint16_t len_item)
{
	static struct ringbuf r;

	if (len_item <= 0)
		return NULL;

	r.buf = malloc(num_item * (len_item + sizeof(struct ringbuf_entry)));

	if (r.buf)
	{
		r.len = num_item;
		r.fill = 0;
		r.slen = (len_item + sizeof(struct ringbuf_entry));

		memset(r.buf, 0, num_item * len_item);

		return &r;
	}

	return NULL;
}