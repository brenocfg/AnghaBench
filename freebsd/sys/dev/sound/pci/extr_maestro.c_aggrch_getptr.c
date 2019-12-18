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
typedef  int u_int32_t ;
struct agg_rchinfo {int hwptr; scalar_t__ stereo; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */

__attribute__((used)) static u_int32_t
aggrch_getptr(kobj_t obj, void *sc)
{
	struct agg_rchinfo *ch = sc;

	return ch->stereo? ch->hwptr << 2 : ch->hwptr << 1;
}