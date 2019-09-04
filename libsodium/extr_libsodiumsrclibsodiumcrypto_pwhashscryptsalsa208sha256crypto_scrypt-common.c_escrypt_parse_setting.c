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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ decode64_one (int /*<<< orphan*/ *,char const) ; 
 char* decode64_uint32 (int /*<<< orphan*/ *,int,char const*) ; 

const uint8_t *
escrypt_parse_setting(const uint8_t *setting,
                      uint32_t *N_log2_p, uint32_t *r_p, uint32_t *p_p)
{
    const uint8_t *src;

    if (setting[0] != '$' || setting[1] != '7' || setting[2] != '$') {
        return NULL;
    }
    src = setting + 3;

    if (decode64_one(N_log2_p, *src)) {
        return NULL;
    }
    src++;

    src = decode64_uint32(r_p, 30, src);
    if (!src) {
        return NULL;
    }

    src = decode64_uint32(p_p, 30, src);
    if (!src) {
        return NULL;
    }
    return src;
}