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
struct tr_chinfo {int ctrl; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int tr_fmttobits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
trpchan_setformat(kobj_t obj, void *data, u_int32_t format)
{
	struct tr_chinfo *ch = data;

	ch->ctrl = tr_fmttobits(format) | 0x01;

	return 0;
}