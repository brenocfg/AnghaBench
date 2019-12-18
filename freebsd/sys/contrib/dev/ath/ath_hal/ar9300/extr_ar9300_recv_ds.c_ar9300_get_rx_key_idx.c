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
typedef  scalar_t__ u_int8_t ;
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_ENOTSUPP ; 
 scalar_t__ HAL_RXKEYIX_INVALID ; 

HAL_STATUS
ar9300_get_rx_key_idx(struct ath_hal *ah, struct ath_desc *ds, u_int8_t *keyix,
    u_int8_t *status)
{
    *status = 0;
    *keyix = HAL_RXKEYIX_INVALID;    
    return HAL_ENOTSUPP;
}