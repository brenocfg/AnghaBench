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
 size_t crypto_kdf_blake2b_CONTEXTBYTES ; 

size_t
crypto_kdf_blake2b_contextbytes(void)
{
    return crypto_kdf_blake2b_CONTEXTBYTES;
}