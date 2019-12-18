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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int QUICLY_TRANSPORT_ERROR_TRANSPORT_PARAMETER ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  quicly_decodev (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 

int quicly_tls_decode_varint(uint64_t *value, const uint8_t **src, const uint8_t *end)
{
    if ((*value = quicly_decodev(src, end)) == UINT64_MAX)
        return QUICLY_TRANSPORT_ERROR_TRANSPORT_PARAMETER;
    return 0;
}