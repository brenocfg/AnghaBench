#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* (* gmalloc ) (size_t,char const*,int) ;} ;

/* Variables and functions */
 TYPE_1__ std_alloc ; 
 void* stub1 (size_t,char const*,int) ; 

__attribute__((used)) static void *oom_malloc(size_t n, const char *file, int line)
{
	/* Reject any allocation of more than 100 bytes */
	return (n > 100) ? NULL : std_alloc.gmalloc(n, file, line);
}