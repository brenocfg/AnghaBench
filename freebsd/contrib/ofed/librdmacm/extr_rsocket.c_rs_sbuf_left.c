#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct rsocket {size_t sbuf_size; TYPE_1__* ssgl; int /*<<< orphan*/ * sbuf; } ;
struct TYPE_2__ {scalar_t__ addr; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t rs_sbuf_left(struct rsocket *rs)
{
	return (uint32_t) (((uint64_t) (uintptr_t) &rs->sbuf[rs->sbuf_size]) -
			   rs->ssgl[0].addr);
}