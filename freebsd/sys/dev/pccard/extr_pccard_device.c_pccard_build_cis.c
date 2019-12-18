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
typedef  int uint8_t ;
struct pccard_tuple {scalar_t__ code; int length; } ;
struct cis_buffer {int len; scalar_t__* buffer; } ;

/* Variables and functions */
 scalar_t__ CISTPL_END ; 
 int ENOSPC ; 
 int pccard_tuple_read_1 (struct pccard_tuple const*,int) ; 

__attribute__((used)) static int
pccard_build_cis(const struct pccard_tuple *tuple, void *argp)
{
	struct cis_buffer *cis;
	int i;
	uint8_t ch;

	cis = (struct cis_buffer *)argp;
	/*
	 * CISTPL_END is a special case, it has no length field.
	 */
	if (tuple->code == CISTPL_END) {
		if (cis->len + 1 > sizeof(cis->buffer))
			return (ENOSPC);
		cis->buffer[cis->len++] = tuple->code;
		return (0);
	}
	if (cis->len + 2 + tuple->length > sizeof(cis->buffer))
		return (ENOSPC);
	cis->buffer[cis->len++] = tuple->code;
	cis->buffer[cis->len++] = tuple->length;
	for (i = 0; i < tuple->length; i++) {
		ch = pccard_tuple_read_1(tuple, i);
		cis->buffer[cis->len++] = ch;
	}
	return (0);
}