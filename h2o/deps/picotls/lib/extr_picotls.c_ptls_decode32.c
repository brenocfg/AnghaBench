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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int PTLS_ALERT_DECODE_ERROR ; 
 int /*<<< orphan*/  ntoh32 (int /*<<< orphan*/  const*) ; 

int ptls_decode32(uint32_t *value, const uint8_t **src, const uint8_t *end)
{
    if (end - *src < 4)
        return PTLS_ALERT_DECODE_ERROR;
    *value = ntoh32(*src);
    *src += 4;
    return 0;
}