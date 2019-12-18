#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char const* ptr; scalar_t__ count; scalar_t__ byte; } ;
typedef  TYPE_1__ unpack_t ;

/* Variables and functions */

__attribute__((used)) static unsigned short unpack_init (unpack_t *t, const unsigned char *ptr)
{
	unsigned short len;

	len = *ptr++;
	len |= *ptr++ << 8;
	t->ptr = ptr;
	t->byte = 0;
	t->count = 0;
	return len;
}