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
typedef  int /*<<< orphan*/  uint32_t ;
struct rib_head {int dummy; } ;
struct mtuex_arg {struct rib_head* rnh; } ;

/* Variables and functions */

__attribute__((used)) static void
in6_mtutimo_setwa(struct rib_head *rnh, uint32_t fibum, int af,
    void *_arg)
{
	struct mtuex_arg *arg;

	arg = (struct mtuex_arg *)_arg;

	arg->rnh = rnh;
}