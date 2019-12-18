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
struct sockaddr {int dummy; } ;
struct TYPE_3__ {struct sockaddr const sa; } ;
typedef  TYPE_1__ BIO_ADDR ;

/* Variables and functions */

const struct sockaddr *BIO_ADDR_sockaddr(const BIO_ADDR *ap)
{
    return &(ap->sa);
}