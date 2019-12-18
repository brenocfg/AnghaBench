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
struct udl_cmd_buf {scalar_t__ off; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int*,scalar_t__,int) ; 
 int htobe32 (int) ; 

__attribute__((used)) static void
udl_cmd_insert_int_3(struct udl_cmd_buf *cb, uint32_t value)
{
	uint32_t lvalue;

#if BYTE_ORDER == BIG_ENDIAN
	lvalue = htobe32(value) << 8;
#else
	lvalue = htobe32(value) >> 8;
#endif
	bcopy(&lvalue, cb->buf + cb->off, 3);

	cb->off += 3;
}