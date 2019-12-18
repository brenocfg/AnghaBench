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
struct regional {size_t first_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (int) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  regional_init (struct regional*) ; 

struct regional* 
regional_create_custom(size_t size)
{
	struct regional* r = (struct regional*)malloc(size);
	log_assert(sizeof(struct regional) <= size);
	if(!r) return NULL;
	r->first_size = size;
	regional_init(r);
	return r;
}