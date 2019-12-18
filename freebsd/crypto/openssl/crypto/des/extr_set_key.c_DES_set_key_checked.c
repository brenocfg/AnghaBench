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
typedef  int /*<<< orphan*/  const_DES_cblock ;
typedef  int /*<<< orphan*/  DES_key_schedule ;

/* Variables and functions */
 int /*<<< orphan*/  DES_check_key_parity (int /*<<< orphan*/ *) ; 
 scalar_t__ DES_is_weak_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DES_set_key_unchecked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int DES_set_key_checked(const_DES_cblock *key, DES_key_schedule *schedule)
{
    if (!DES_check_key_parity(key))
        return -1;
    if (DES_is_weak_key(key))
        return -2;
    DES_set_key_unchecked(key, schedule);
    return 0;
}