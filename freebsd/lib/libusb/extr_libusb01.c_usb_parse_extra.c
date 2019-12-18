#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/ * currextra; } ;
struct TYPE_6__ {TYPE_2__* currextra; } ;
struct usb_parse_state {scalar_t__ preparse; TYPE_1__ b; TYPE_3__ a; } ;
struct TYPE_5__ {int len; void* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static void
usb_parse_extra(struct usb_parse_state *ps, uint8_t **pptr, int *plen)
{
	void *ptr;
	uint16_t len;

	ptr = ps->a.currextra->ptr;
	len = ps->a.currextra->len;

	if (ps->preparse == 0) {
		memcpy(ps->b.currextra, ptr, len);
		*pptr = ps->b.currextra;
		*plen = len;
	}
	ps->b.currextra += len;
	return;
}