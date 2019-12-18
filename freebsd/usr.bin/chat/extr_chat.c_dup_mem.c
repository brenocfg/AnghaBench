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
 int /*<<< orphan*/  fatal (int,char*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

void *
dup_mem(void *b, size_t c)
{
    void *ans = malloc (c);
    if (!ans)
	fatal(2, "memory error!");

    memcpy (ans, b, c);
    return ans;
}