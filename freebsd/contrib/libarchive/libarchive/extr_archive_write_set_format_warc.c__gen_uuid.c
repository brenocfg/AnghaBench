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
struct TYPE_3__ {int* u; } ;
typedef  TYPE_1__ warc_uuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  archive_random (int*,int) ; 

__attribute__((used)) static int
_gen_uuid(warc_uuid_t *tgt)
{
	archive_random(tgt->u, sizeof(tgt->u));
	/* obey uuid version 4 rules */
	tgt->u[1U] &= 0xffff0fffU;
	tgt->u[1U] |= 0x4000U;
	tgt->u[2U] &= 0x3fffffffU;
	tgt->u[2U] |= 0x80000000U;
	return 0;
}