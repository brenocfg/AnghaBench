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
typedef  int /*<<< orphan*/  RAND_DRBG ;

/* Variables and functions */
 int RAND_DRBG_bytes (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/ * RAND_DRBG_get0_public () ; 

__attribute__((used)) static int drbg_bytes(unsigned char *out, int count)
{
    int ret;
    RAND_DRBG *drbg = RAND_DRBG_get0_public();

    if (drbg == NULL)
        return 0;

    ret = RAND_DRBG_bytes(drbg, out, count);

    return ret;
}