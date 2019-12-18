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
struct TYPE_4__ {int* base; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ uv_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_buffer (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ random () ; 

uv_buf_t make_discover_msg() {
    uv_buf_t buffer;
    alloc_buffer(NULL, 256, &buffer);
    memset(buffer.base, 0, buffer.len);

    // BOOTREQUEST
    buffer.base[0] = 0x1;
    // HTYPE ethernet
    buffer.base[1] = 0x1;
    // HLEN
    buffer.base[2] = 0x6;
    // HOPS
    buffer.base[3] = 0x0;
    // XID 4 bytes
    buffer.base[4] = (unsigned int) random();
    // SECS
    buffer.base[8] = 0x0;
    // FLAGS
    buffer.base[10] = 0x80;
    // CIADDR 12-15 is all zeros
    // YIADDR 16-19 is all zeros
    // SIADDR 20-23 is all zeros
    // GIADDR 24-27 is all zeros
    // CHADDR 28-43 is the MAC address, use your own
    buffer.base[28] = 0xe4;
    buffer.base[29] = 0xce;
    buffer.base[30] = 0x8f;
    buffer.base[31] = 0x13;
    buffer.base[32] = 0xf6;
    buffer.base[33] = 0xd4;
    // SNAME 64 bytes zero
    // FILE 128 bytes zero
    // OPTIONS
    // - magic cookie
    buffer.base[236] = 99;
    buffer.base[237] = 130;
    buffer.base[238] = 83;
    buffer.base[239] = 99;

    // DHCP Message type
    buffer.base[240] = 53;
    buffer.base[241] = 1;
    buffer.base[242] = 1; // DHCPDISCOVER

    // DHCP Parameter request list
    buffer.base[243] = 55;
    buffer.base[244] = 4;
    buffer.base[245] = 1;
    buffer.base[246] = 3;
    buffer.base[247] = 15;
    buffer.base[248] = 6;

    return buffer;
}