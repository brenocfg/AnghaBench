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
typedef  scalar_t__ u_int16_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR9300_DEVID_AR9340 ; 
 int /*<<< orphan*/  ar9300_init_hostif_offsets (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9340_init_hostif_offsets (struct ath_hal*) ; 

__attribute__((used)) static int ar9300_init_offsets(struct ath_hal *ah, u_int16_t devid)
{
    if (devid == AR9300_DEVID_AR9340) {
        ar9340_init_hostif_offsets(ah);
    } else {
        ar9300_init_hostif_offsets(ah);
    }
    return 0;
}