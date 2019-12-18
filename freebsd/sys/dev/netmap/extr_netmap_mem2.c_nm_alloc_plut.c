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
typedef  int u_int ;
struct plut_entry {int dummy; } ;

/* Variables and functions */
 struct plut_entry* vmalloc (size_t) ; 

__attribute__((used)) static struct plut_entry *
nm_alloc_plut(u_int nobj)
{
	size_t n = sizeof(struct plut_entry) * nobj;
	struct plut_entry *lut;
	lut = vmalloc(n);
	return lut;
}