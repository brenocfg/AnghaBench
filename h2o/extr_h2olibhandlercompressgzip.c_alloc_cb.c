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
 void* h2o_mem_alloc (unsigned int) ; 

__attribute__((used)) static void *alloc_cb(void *_unused, unsigned int cnt, unsigned int sz)
{
    return h2o_mem_alloc(cnt * (size_t)sz);
}