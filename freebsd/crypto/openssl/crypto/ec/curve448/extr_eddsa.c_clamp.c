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
typedef  int uint8_t ;

/* Variables and functions */
 int COFACTOR ; 
 int EDDSA_448_PRIVATE_BYTES ; 

__attribute__((used)) static void clamp(uint8_t secret_scalar_ser[EDDSA_448_PRIVATE_BYTES])
{
    secret_scalar_ser[0] &= -COFACTOR;
    secret_scalar_ser[EDDSA_448_PRIVATE_BYTES - 1] = 0;
    secret_scalar_ser[EDDSA_448_PRIVATE_BYTES - 2] |= 0x80;
}