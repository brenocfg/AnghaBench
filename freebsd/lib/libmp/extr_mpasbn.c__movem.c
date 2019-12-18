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
 int /*<<< orphan*/  BN_ERRCHECK (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_movem(const char *msg, const MINT *smp, MINT *tmp)
{

	BN_ERRCHECK(msg, BN_copy(tmp->bn, smp->bn));
}