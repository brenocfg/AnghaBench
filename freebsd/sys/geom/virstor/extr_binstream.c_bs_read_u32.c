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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ pos; scalar_t__ data; } ;
typedef  TYPE_1__ bin_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  le32dec (scalar_t__) ; 

uint32_t
bs_read_u32(bin_stream_t * bs)
{
	uint32_t	data = le32dec(bs->data + bs->pos);
	bs->pos += 4;
	return data;
}