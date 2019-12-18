#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bn; } ;
typedef  TYPE_1__ MINT ;

/* Variables and functions */
 int BN_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
mp_mcmp(const MINT *mp1, const MINT *mp2)
{

	return (BN_cmp(mp1->bn, mp2->bn));
}