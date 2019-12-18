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
struct md_s {int /*<<< orphan*/  uma; } ;
struct indir {int* array; scalar_t__ shift; } ;

/* Variables and functions */
 int NINDIR ; 
 int /*<<< orphan*/  del_indir (struct indir*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
destroy_indir(struct md_s *sc, struct indir *ip)
{
	int i;

	for (i = 0; i < NINDIR; i++) {
		if (!ip->array[i])
			continue;
		if (ip->shift)
			destroy_indir(sc, (struct indir*)(ip->array[i]));
		else if (ip->array[i] > 255)
			uma_zfree(sc->uma, (void *)(ip->array[i]));
	}
	del_indir(ip);
}