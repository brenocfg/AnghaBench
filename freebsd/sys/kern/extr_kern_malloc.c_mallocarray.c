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
struct malloc_type {int dummy; } ;

/* Variables and functions */
 scalar_t__ WOULD_OVERFLOW (size_t,size_t) ; 
 void* malloc (size_t,struct malloc_type*,int) ; 
 int /*<<< orphan*/  panic (char*,size_t,size_t) ; 

void *
mallocarray(size_t nmemb, size_t size, struct malloc_type *type, int flags)
{

	if (WOULD_OVERFLOW(nmemb, size))
		panic("mallocarray: %zu * %zu overflowed", nmemb, size);

	return (malloc(size * nmemb, type, flags));
}