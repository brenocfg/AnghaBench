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
struct torus {int /*<<< orphan*/ *** sw; int /*<<< orphan*/  z_sz; int /*<<< orphan*/  y_sz; } ;

/* Variables and functions */
 int canonicalize (int,int /*<<< orphan*/ ) ; 
 scalar_t__ install_tswitch (struct torus*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_no_perp (struct torus*,int,int,int,int,int,int,int) ; 
 scalar_t__ safe_y_perpendicular (struct torus*,int,int,int) ; 
 int /*<<< orphan*/  tfind_2d_perpendicular (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
bool handle_case_0x644(struct torus *t, int i, int j, int k)
{
	int jm1 = canonicalize(j - 1, t->y_sz);
	int jp1 = canonicalize(j + 1, t->y_sz);
	int kp1 = canonicalize(k + 1, t->z_sz);

	if (safe_y_perpendicular(t, i, j, k) &&
	    install_tswitch(t, i, jp1, k,
			    tfind_2d_perpendicular(t->sw[i][j][kp1],
						   t->sw[i][j][k],
						   t->sw[i][jm1][k]))) {
		return true;
	}
	log_no_perp(t, 0x644, i, j, k, i, j, k);

	if (safe_y_perpendicular(t, i, j, kp1) &&
	    install_tswitch(t, i, jp1, kp1,
			    tfind_2d_perpendicular(t->sw[i][j][k],
						   t->sw[i][j][kp1],
						   t->sw[i][jm1][kp1]))) {
		return true;
	}
	log_no_perp(t, 0x644, i, j, k, i, j, kp1);
	return false;
}