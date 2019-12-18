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
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  cid; } ;
typedef  TYPE_1__ quicly_cid_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline uint8_t *emit_cid(uint8_t *dst, const quicly_cid_t *cid)
{
    if (cid->len != 0) {
        memcpy(dst, cid->cid, cid->len);
        dst += cid->len;
    }
    return dst;
}