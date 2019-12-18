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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  quicly_address_t ;
struct TYPE_3__ {int len; scalar_t__ base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 scalar_t__ H2O_QUIC_FORWARDED_VERSION ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  decode_quic_address (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 scalar_t__ quicly_decode32 (int /*<<< orphan*/  const**) ; 

__attribute__((used)) static size_t decode_quic_forwarded_header(quicly_address_t *destaddr, quicly_address_t *srcaddr, uint8_t *ttl, h2o_iovec_t octets)
{
    const uint8_t *src = (uint8_t *)octets.base, *end = src + octets.len;

    if (end - src < 6)
        goto NotForwarded;
    if (*src++ != 0x80)
        goto NotForwarded;
    if (quicly_decode32(&src) != H2O_QUIC_FORWARDED_VERSION)
        goto NotForwarded;
    if (!decode_quic_address(destaddr, &src, end))
        goto NotForwarded;
    if (!decode_quic_address(srcaddr, &src, end))
        goto NotForwarded;
    if (end - src < 1)
        goto NotForwarded;
    *ttl = *src++;

    return src - (const uint8_t *)octets.base;
NotForwarded:
    return SIZE_MAX;
}