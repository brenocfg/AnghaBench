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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ad1816_chinfo {int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  sndbuf_dmaptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
ad1816chan_getptr(kobj_t obj, void *data)
{
	struct ad1816_chinfo *ch = data;
	return sndbuf_dmaptr(ch->buffer);
}