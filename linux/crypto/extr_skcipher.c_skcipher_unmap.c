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
struct scatter_walk {int dummy; } ;

/* Variables and functions */
 scalar_t__ PageHighMem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  scatterwalk_page (struct scatter_walk*) ; 

__attribute__((used)) static inline void skcipher_unmap(struct scatter_walk *walk, void *vaddr)
{
	if (PageHighMem(scatterwalk_page(walk)))
		kunmap_atomic(vaddr);
}