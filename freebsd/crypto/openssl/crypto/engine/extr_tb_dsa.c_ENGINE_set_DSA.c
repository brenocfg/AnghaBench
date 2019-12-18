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
struct TYPE_3__ {int /*<<< orphan*/  const* dsa_meth; } ;
typedef  TYPE_1__ ENGINE ;
typedef  int /*<<< orphan*/  DSA_METHOD ;

/* Variables and functions */

int ENGINE_set_DSA(ENGINE *e, const DSA_METHOD *dsa_meth)
{
    e->dsa_meth = dsa_meth;
    return 1;
}