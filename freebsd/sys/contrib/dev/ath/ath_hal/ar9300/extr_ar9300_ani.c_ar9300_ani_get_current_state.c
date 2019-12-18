#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
struct ar9300_ani_state {int dummy; } ;
struct TYPE_2__ {struct ar9300_ani_state* ah_curani; } ;

/* Variables and functions */
 TYPE_1__* AH9300 (struct ath_hal*) ; 

struct ar9300_ani_state *
ar9300_ani_get_current_state(struct ath_hal *ah)
{
    return AH9300(ah)->ah_curani;
}