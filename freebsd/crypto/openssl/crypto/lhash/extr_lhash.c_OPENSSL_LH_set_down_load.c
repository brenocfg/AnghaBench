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
struct TYPE_3__ {unsigned long down_load; } ;
typedef  TYPE_1__ OPENSSL_LHASH ;

/* Variables and functions */

void OPENSSL_LH_set_down_load(OPENSSL_LHASH *lh, unsigned long down_load)
{
    lh->down_load = down_load;
}