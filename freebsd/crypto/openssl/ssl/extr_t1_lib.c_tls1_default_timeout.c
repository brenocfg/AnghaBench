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

long tls1_default_timeout(void)
{
    /*
     * 2 hours, the 24 hours mentioned in the TLSv1 spec is way too long for
     * http, the cache would over fill
     */
    return (60 * 60 * 2);
}