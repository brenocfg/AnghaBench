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
struct TYPE_2__ {struct resource_i* __r_i; } ;
struct resource_i {TYPE_1__ r_r; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_RMAN ; 
 int M_ZERO ; 
 struct resource_i* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline struct resource_i *
int_alloc_resource(int malloc_flag)
{
	struct resource_i *r;

	r = malloc(sizeof *r, M_RMAN, malloc_flag | M_ZERO);
	if (r != NULL) {
		r->r_r.__r_i = r;
	}
	return (r);
}