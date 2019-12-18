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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int data; int pos; } ;
typedef  TYPE_1__ bin_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  le16enc (int,int /*<<< orphan*/ ) ; 

unsigned
bs_write_u16(bin_stream_t * bs, uint16_t data)
{
	le16enc(bs->data + bs->pos, data);
	return (bs->pos += 2);
}