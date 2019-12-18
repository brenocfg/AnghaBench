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
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ DH ;

/* Variables and functions */
 int /*<<< orphan*/  DH_FLAG_CACHE_MONT_P ; 

__attribute__((used)) static int dh_init(DH *dh)
{
    dh->flags |= DH_FLAG_CACHE_MONT_P;
    return 1;
}