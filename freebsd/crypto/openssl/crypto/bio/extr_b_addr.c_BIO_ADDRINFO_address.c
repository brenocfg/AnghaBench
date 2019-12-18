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
struct TYPE_3__ {scalar_t__ bai_addr; } ;
typedef  TYPE_1__ BIO_ADDRINFO ;
typedef  int /*<<< orphan*/  const BIO_ADDR ;

/* Variables and functions */

const BIO_ADDR *BIO_ADDRINFO_address(const BIO_ADDRINFO *bai)
{
    if (bai != NULL)
        return (BIO_ADDR *)bai->bai_addr;
    return NULL;
}