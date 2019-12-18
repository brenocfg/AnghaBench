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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,size_t) ; 
 void* realloc (void*,size_t) ; 

void *srealloc(void *ptr, size_t size) {
    void *result = realloc(ptr, size);
    if (result == NULL && size > 0)
        err(EXIT_FAILURE, "realloc(%zd)", size);
    return result;
}