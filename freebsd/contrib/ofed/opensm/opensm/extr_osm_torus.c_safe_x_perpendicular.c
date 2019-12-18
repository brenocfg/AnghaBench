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
struct torus {int dummy; } ;

/* Variables and functions */
 scalar_t__ safe_y_ring (struct torus*,int,int,int) ; 
 scalar_t__ safe_z_ring (struct torus*,int,int,int) ; 

__attribute__((used)) static
bool safe_x_perpendicular(struct torus *t, int i, int j, int k)
{
	/*
	 * If the dimensions perpendicular to the search direction are
	 * not radix 4 torus dimensions, it is always safe to search for
	 * a perpendicular.
	 *
	 * Here we are checking for enough appropriate links having been
	 * installed into the torus to prevent an incorrect link from being
	 * considered as a perpendicular candidate.
	 */
	return safe_y_ring(t, i, j, k) && safe_z_ring(t, i, j, k);
}