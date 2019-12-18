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
 int /*<<< orphan*/  serf_bucket_mem_free (void*,char*) ; 

__attribute__((used)) static void free_copied_data(void *baton, const char *data)
{
    serf_bucket_mem_free(baton, (char*)data);
}