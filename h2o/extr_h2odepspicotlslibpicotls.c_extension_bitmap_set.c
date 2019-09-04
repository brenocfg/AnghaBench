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
typedef  int uint16_t ;
struct st_ptls_extension_bitmap_t {int* bits; } ;

/* Variables and functions */

__attribute__((used)) static inline void extension_bitmap_set(struct st_ptls_extension_bitmap_t *bitmap, uint16_t id)
{
    if (id < sizeof(bitmap->bits) * 8)
        bitmap->bits[id / 8] |= 1 << (id % 8);
}