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
typedef  int UINT64 ;
typedef  int /*<<< orphan*/  UINT32 ;

/* Variables and functions */
 int m36 ; 
 int p36 ; 

__attribute__((used)) static UINT32 ip_reduce_p36(UINT64 t)
{
/* Divisionless modular reduction */
    UINT64 ret;

    ret = (t & m36) + 5 * (t >> 36);
    if (ret >= p36)
        ret -= p36;

    /* return least significant 32 bits */
    return (UINT32)(ret);
}