#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ id; } ;
typedef  TYPE_1__ SSL_CIPHER ;

/* Variables and functions */

__attribute__((used)) static int cipher_compare(const void *a, const void *b)
{
    const SSL_CIPHER *ap = (const SSL_CIPHER *)a;
    const SSL_CIPHER *bp = (const SSL_CIPHER *)b;

    if (ap->id == bp->id)
        return 0;
    return ap->id < bp->id ? -1 : 1;
}