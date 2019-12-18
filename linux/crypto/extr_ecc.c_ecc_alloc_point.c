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
struct ecc_point {unsigned int ndigits; void* x; void* y; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* ecc_alloc_digits_space (unsigned int) ; 
 int /*<<< orphan*/  ecc_free_digits_space (void*) ; 
 int /*<<< orphan*/  kfree (struct ecc_point*) ; 
 struct ecc_point* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ecc_point *ecc_alloc_point(unsigned int ndigits)
{
	struct ecc_point *p = kmalloc(sizeof(*p), GFP_KERNEL);

	if (!p)
		return NULL;

	p->x = ecc_alloc_digits_space(ndigits);
	if (!p->x)
		goto err_alloc_x;

	p->y = ecc_alloc_digits_space(ndigits);
	if (!p->y)
		goto err_alloc_y;

	p->ndigits = ndigits;

	return p;

err_alloc_y:
	ecc_free_digits_space(p->x);
err_alloc_x:
	kfree(p);
	return NULL;
}