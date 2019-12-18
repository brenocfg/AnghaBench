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

/* Variables and functions */

int bit_insert ( int srcvec,           // srcvec[0] = bit to be inserted
                 int dstbitpos,        // Bit position to insert into returned int
                 int dstvec            // dstvec (destination vector)
               )
{
    return((srcvec << dstbitpos) | dstvec);      // Shift bit to insert into bit position/OR with accumulated number
}