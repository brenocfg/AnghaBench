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
 int /*<<< orphan*/  log_no_crnr (struct torus*,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  tfind_face_corner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
bool handle_case_0x713(struct torus *t, int i, int j, int k)
{
	int ip1 = canonicalize(i + 1, t->x_sz);
	int jp1 = canonicalize(j + 1, t->y_sz);
	int kp1 = canonicalize(k + 1, t->z_sz);

	if (install_tswitch(t, ip1, j, k,
			    tfind_face_corner(t->sw[ip1][jp1][k],
					      t->sw[ip1][jp1][kp1],
					      t->sw[ip1][j][kp1]))) {
		return true;
	}
	log_no_crnr(t, 0x713, i, j, k, ip1, j, k);

	if (install_tswitch(t, i, j, kp1,
			    tfind_face_corner(t->sw[ip1][j][kp1],
					      t->sw[ip1][jp1][kp1],
					      t->sw[i][jp1][kp1]))) {
		return true;
	}
	log_no_crnr(t, 0x713, i, j, k, i, j, kp1);
	return false;
}