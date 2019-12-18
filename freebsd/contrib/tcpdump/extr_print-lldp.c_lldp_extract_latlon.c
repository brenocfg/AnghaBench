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
typedef  int uint64_t ;
typedef  int u_char ;

/* Variables and functions */
 int EXTRACT_32BITS (int const*) ; 

__attribute__((used)) static uint64_t
lldp_extract_latlon(const u_char *tptr)
{
    uint64_t latlon;

    latlon = *tptr & 0x3;
    latlon = (latlon << 32) | EXTRACT_32BITS(tptr+1);

    return latlon;
}