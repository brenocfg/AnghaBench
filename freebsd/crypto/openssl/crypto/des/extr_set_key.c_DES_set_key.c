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
 scalar_t__ DES_check_key ; 
 int DES_set_key_checked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DES_set_key_unchecked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int DES_set_key(const_DES_cblock *key, DES_key_schedule *schedule)
{
    if (DES_check_key) {
        return DES_set_key_checked(key, schedule);
    } else {
        DES_set_key_unchecked(key, schedule);
        return 0;
    }
}