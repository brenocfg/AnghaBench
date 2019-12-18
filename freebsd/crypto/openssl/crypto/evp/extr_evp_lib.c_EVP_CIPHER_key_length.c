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
struct TYPE_3__ {int key_len; } ;
typedef  TYPE_1__ EVP_CIPHER ;

/* Variables and functions */

int EVP_CIPHER_key_length(const EVP_CIPHER *cipher)
{
    return cipher->key_len;
}