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
struct torus {int /*<<< orphan*/ *** sw; int /*<<< orphan*/  z_sz; int /*<<< orphan*/  x_sz; } ;

/* Variables and functions */
 int canonicalize (int,int /*<<< orphan*/ ) ; 
 scalar_t__ install_tswitch (struct torus*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_no_perp (struct torus*,int,int,int,int,int,int,int) ; 
 scalar_t__ safe_z_perpendicular (struct torus*,int,int,int) ; 
 int /*<<< orphan*/  tfind_2d_perpendicular (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
bool handle_case_0x530(struct torus *t, int i, int j, int k)
{
	int ip1 = canonicalize(i + 1, t->x_sz);
	int km1 = canonicalize(k - 1, t->z_sz);
	int kp1 = canonicalize(k + 1, t->z_sz);

	if (safe_z_perpendicular(t, i, j, k) &&
	    install_tswitch(t, i, j, kp1,
			    tfind_2d_perpendicular(t->sw[ip1][j][k],
						   t->sw[i][j][k],
						   t->sw[i][j][km1]))) {
		return true;
	}
	log_no_perp(t, 0x530, i, j, k, i, j, k);

	if (safe_z_perpendicular(t, ip1, j, k) &&
	      install_tswitch(t, ip1, j, kp1,
			      tfind_2d_perpendicular(t->sw[i][j][k],
						     t->sw[ip1][j][k],
						     t->sw[ip1][j][km1]))) {
		return true;
	}
	log_no_perp(t, 0x530, i, j, k, ip1, j, k);
	return false;
}