#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int flags; } ;
typedef  TYPE_1__ krb5_crypto_iov ;

/* Variables and functions */

__attribute__((used)) static krb5_crypto_iov *
find_iv(krb5_crypto_iov *data, size_t num_data, unsigned type)
{
    size_t i;
    for (i = 0; i < num_data; i++)
	if (data[i].flags == type)
	    return &data[i];
    return NULL;
}