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
struct torus {int /*<<< orphan*/ *** sw; int /*<<< orphan*/  z_sz; int /*<<< orphan*/  y_sz; int /*<<< orphan*/  x_sz; } ;

/* Variables and functions */
 int canonicalize (int,int /*<<< orphan*/ ) ; 
 scalar_t__ install_tswitch (struct torus*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_no_perp (struct torus*,int,int,int,int,int,int,int) ; 
 scalar_t__ safe_z_perpendicular (struct torus*,int,int,int) ; 
 int /*<<< orphan*/  tfind_3d_perpendicular (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
bool handle_case_0x78f(struct torus *t, int i, int j, int k)
{
	int ip1 = canonicalize(i + 1, t->x_sz);
	int jp1 = canonicalize(j + 1, t->y_sz);
	int kp1 = canonicalize(k + 1, t->z_sz);
	int kp2 = canonicalize(k + 2, t->z_sz);

	if (safe_z_perpendicular(t, i, j, kp1) &&
	    install_tswitch(t, i, j, k,
			    tfind_3d_perpendicular(t->sw[ip1][j][kp1],
						   t->sw[i][j][kp1],
						   t->sw[i][jp1][kp1],
						   t->sw[i][j][kp2]))) {
		return true;
	}
	log_no_perp(t, 0x78f, i, j, k, i, j, kp1);
	return false;
}