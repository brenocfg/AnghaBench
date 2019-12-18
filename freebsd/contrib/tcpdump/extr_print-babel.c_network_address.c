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
 int network_prefix (int,int,int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ *,unsigned int,unsigned char*) ; 

__attribute__((used)) static int
network_address(int ae, const unsigned char *a, unsigned int len,
                unsigned char *a_r)
{
    return network_prefix(ae, -1, 0, a, NULL, len, a_r);
}