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
struct translation {int key; } ;

/* Variables and functions */

__attribute__((used)) static int
translation_cmp(const void *key, const void *data)
{
    const struct translation *t1 = (const struct translation *)key;
    const struct translation *t2 = (const struct translation *)data;

    return t1->key - t2->key;
}