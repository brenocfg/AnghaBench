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
typedef  int /*<<< orphan*/  RAND_METHOD ;
typedef  int /*<<< orphan*/  RAND_DRBG ;

/* Variables and functions */
 int RAND_DRBG_bytes (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/ * RAND_DRBG_get0_private () ; 
 int /*<<< orphan*/  const* RAND_OpenSSL () ; 
 int RAND_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/ * RAND_get_rand_method () ; 

int RAND_priv_bytes(unsigned char *buf, int num)
{
    const RAND_METHOD *meth = RAND_get_rand_method();
    RAND_DRBG *drbg;
    int ret;

    if (meth != RAND_OpenSSL())
        return RAND_bytes(buf, num);

    drbg = RAND_DRBG_get0_private();
    if (drbg == NULL)
        return 0;

    ret = RAND_DRBG_bytes(drbg, buf, num);
    return ret;
}