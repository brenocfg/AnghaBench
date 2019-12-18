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
struct TYPE_4__ {size_t written; size_t curr; } ;
typedef  TYPE_1__ WPACKET ;

/* Variables and functions */
 int /*<<< orphan*/  WPACKET_reserve_bytes (TYPE_1__*,size_t,unsigned char**) ; 

int WPACKET_allocate_bytes(WPACKET *pkt, size_t len, unsigned char **allocbytes)
{
    if (!WPACKET_reserve_bytes(pkt, len, allocbytes))
        return 0;

    pkt->written += len;
    pkt->curr += len;
    return 1;
}