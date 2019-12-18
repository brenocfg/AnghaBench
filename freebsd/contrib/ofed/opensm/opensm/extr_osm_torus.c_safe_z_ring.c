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
struct torus {int z_sz; int flags; scalar_t__*** sw; } ;

/* Variables and functions */
 int Z_MESH ; 
 int canonicalize (int,int) ; 
 scalar_t__ link_tswitches (struct torus*,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static
bool safe_z_ring(struct torus *t, int i, int j, int k)
{
	int km1, kp1, kp2;
	bool success = true;

	/*
	 * If this z-direction radix-4 ring has at least two links
	 * already installed into the torus,  then this ring does not
	 * prevent us from looking for x or y direction perpendiculars.
	 *
	 * It is easier to check for the appropriate switches being installed
	 * into the torus than it is to check for the links, so force the
	 * link installation if the appropriate switches are installed.
	 *
	 * Recall that canonicalize(n - 2, 4) == canonicalize(n + 2, 4).
	 */
	if (t->z_sz != 4 || t->flags & Z_MESH)
		goto out;

	km1 = canonicalize(k - 1, t->z_sz);
	kp1 = canonicalize(k + 1, t->z_sz);
	kp2 = canonicalize(k + 2, t->z_sz);

	if (!!t->sw[i][j][km1] +
	    !!t->sw[i][j][kp1] + !!t->sw[i][j][kp2] < 2) {
		success = false;
		goto out;
	}
	if (t->sw[i][j][kp2] && t->sw[i][j][km1])
		success = link_tswitches(t, 2,
					 t->sw[i][j][kp2],
					 t->sw[i][j][km1])
			&& success;

	if (t->sw[i][j][km1] && t->sw[i][j][k])
		success = link_tswitches(t, 2,
					 t->sw[i][j][km1],
					 t->sw[i][j][k])
			&& success;

	if (t->sw[i][j][k] && t->sw[i][j][kp1])
		success = link_tswitches(t, 2,
					 t->sw[i][j][k],
					 t->sw[i][j][kp1])
			&& success;

	if (t->sw[i][j][kp1] && t->sw[i][j][kp2])
		success = link_tswitches(t, 2,
					 t->sw[i][j][kp1],
					 t->sw[i][j][kp2])
			&& success;
out:
	return success;
}