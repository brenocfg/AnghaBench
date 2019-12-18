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
struct _krb5_encryption_type {int padsize; scalar_t__ confoundersize; int /*<<< orphan*/  checksum; } ;
typedef  TYPE_1__* krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_3__ {struct _krb5_encryption_type* et; } ;

/* Variables and functions */
 size_t CHECKSUMSIZE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
crypto_overhead (krb5_context context,
		 krb5_crypto  crypto)
{
    struct _krb5_encryption_type *et = crypto->et;
    size_t res;

    res = CHECKSUMSIZE(et->checksum);
    res += et->confoundersize;
    if (et->padsize > 1)
	res += et->padsize;
    return res;
}