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

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline void
remove_from_array(void *array, size_t item_size, size_t idx, size_t array_count) {
    size_t num_to_right = array_count - 1 - idx;
    uint8_t *p = (uint8_t*)array;
    if (num_to_right > 0) memmove(p + (idx * item_size), p + ((idx + 1) * item_size), num_to_right * item_size);
    memset(p + (item_size * (array_count - 1)), 0, item_size);
}