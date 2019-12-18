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
 void* calloc (size_t,size_t) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,size_t,size_t) ; 

void *scalloc(size_t num, size_t size) {
    void *result = calloc(num, size);
    if (result == NULL)
        err(EXIT_FAILURE, "calloc(%zd, %zd)", num, size);
    return result;
}