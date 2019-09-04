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

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  errno ; 
 void* sodium_malloc (size_t) ; 

__attribute__((malloc)) void *
sodium_allocarray(size_t count, size_t size)
{
    if (count > (size_t) 0U && size >= (size_t) SIZE_MAX / count) {
        errno = ENOMEM;
        return NULL;
    }
    return sodium_malloc(count * size);
}