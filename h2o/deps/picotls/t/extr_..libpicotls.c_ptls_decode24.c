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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int PTLS_ALERT_DECODE_ERROR ; 

int ptls_decode24(uint32_t *value, const uint8_t **src, const uint8_t *end)
{
    if (end - *src < 3)
        return PTLS_ALERT_DECODE_ERROR;
    *value = ((uint32_t)(*src)[0] << 16) | ((uint32_t)(*src)[1] << 8) | (*src)[2];
    *src += 3;
    return 0;
}