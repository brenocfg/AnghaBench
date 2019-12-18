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
struct lut_entry {int dummy; } ;

/* Variables and functions */
 struct lut_entry* nm_os_malloc (size_t) ; 
 struct lut_entry* vmalloc (size_t) ; 

__attribute__((used)) static struct lut_entry *
nm_alloc_lut(u_int nobj)
{
	size_t n = sizeof(struct lut_entry) * nobj;
	struct lut_entry *lut;
#ifdef linux
	lut = vmalloc(n);
#else
	lut = nm_os_malloc(n);
#endif
	return lut;
}