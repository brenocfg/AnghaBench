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
struct regional {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 void* regional_alloc (struct regional*,size_t) ; 

void *
regional_alloc_init(struct regional* r, const void *init, size_t size)
{
	void *s = regional_alloc(r, size);
	if(!s) return NULL;
	memcpy(s, init, size);
	return s;
}