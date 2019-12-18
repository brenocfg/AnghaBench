#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int iv_len; } ;
typedef  TYPE_1__ EVP_CIPHER ;

/* Variables and functions */

int EVP_CIPHER_meth_set_iv_length(EVP_CIPHER *cipher, int iv_len)
{
    cipher->iv_len = iv_len;
    return 1;
}