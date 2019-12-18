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
struct torus {int x_sz; int flags; scalar_t__*** sw; } ;

/* Variables and functions */
 int X_MESH ; 
 int canonicalize (int,int) ; 
 scalar_t__ link_tswitches (struct torus*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static
bool safe_x_ring(struct torus *t, int i, int j, int k)
{
	int im1, ip1, ip2;
	bool success = true;

	/*
	 * If this x-direction radix-4 ring has at least two links
	 * already installed into the torus,  then this ring does not
	 * prevent us from looking for y or z direction perpendiculars.
	 *
	 * It is easier to check for the appropriate switches being installed
	 * into the torus than it is to check for the links, so force the
	 * link installation if the appropriate switches are installed.
	 *
	 * Recall that canonicalize(n - 2, 4) == canonicalize(n + 2, 4).
	 */
	if (t->x_sz != 4 || t->flags & X_MESH)
		goto out;

	im1 = canonicalize(i - 1, t->x_sz);
	ip1 = canonicalize(i + 1, t->x_sz);
	ip2 = canonicalize(i + 2, t->x_sz);

	if (!!t->sw[im1][j][k] +
	    !!t->sw[ip1][j][k] + !!t->sw[ip2][j][k] < 2) {
		success = false;
		goto out;
	}
	if (t->sw[ip2][j][k] && t->sw[im1][j][k])
		success = link_tswitches(t, 0,
					 t->sw[ip2][j][k],
					 t->sw[im1][j][k])
			&& success;

	if (t->sw[im1][j][k] && t->sw[i][j][k])
		success = link_tswitches(t, 0,
					 t->sw[im1][j][k],
					 t->sw[i][j][k])
			&& success;

	if (t->sw[i][j][k] && t->sw[ip1][j][k])
		success = link_tswitches(t, 0,
					 t->sw[i][j][k],
					 t->sw[ip1][j][k])
			&& success;

	if (t->sw[ip1][j][k] && t->sw[ip2][j][k])
		success = link_tswitches(t, 0,
					 t->sw[ip1][j][k],
					 t->sw[ip2][j][k])
			&& success;
out:
	return success;
}