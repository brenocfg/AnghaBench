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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {int exclusive; int dependency; scalar_t__ weight; } ;
typedef  TYPE_1__ h2o_http2_priority_t ;

/* Variables and functions */
 int h2o_http2_decode32u (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const uint8_t *decode_priority(h2o_http2_priority_t *priority, const uint8_t *src)
{
    uint32_t u4 = h2o_http2_decode32u(src);
    src += 4;
    priority->exclusive = u4 >> 31;
    priority->dependency = u4 & 0x7fffffff;
    priority->weight = (uint16_t)*src++ + 1;
    return src;
}