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
 void* malloc (size_t) ; 

void *smalloc(size_t size) {
    void *result = malloc(size);
    if (result == NULL)
        err(EXIT_FAILURE, "malloc(%zd)", size);
    return result;
}