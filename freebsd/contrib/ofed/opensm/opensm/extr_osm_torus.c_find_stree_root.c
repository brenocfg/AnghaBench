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
struct torus {int z_sz; int y_sz; int x_sz; struct t_switch**** sw; } ;
struct t_switch {int dummy; } ;

/* Variables and functions */
 int canonicalize (int,int) ; 
 struct t_switch* find_plane_mid (struct torus*,int) ; 

__attribute__((used)) static
struct t_switch *find_stree_root(struct torus *t)
{
	int x, y, z, dz, zm = t->z_sz / 2;
	struct t_switch ****sw = t->sw;
	struct t_switch *root;
	bool good_plane;

	/*
	 * Look for a switch near the "center" (wrt. the datelines) of the
	 * torus, as that will be the most optimum spanning tree root.  Use
	 * a search that is not exhaustive, on the theory that this routing
	 * engine isn't useful anyway if too many switches are missing.
	 *
	 * Also, want to pick an x-y plane with no missing switches, so that
	 * the master spanning tree construction algorithm doesn't have to
	 * deal with needing a turn on a missing switch.
	 */
	for (dz = 0; dz <= zm; dz++) {

		z = canonicalize(zm - dz, t->z_sz);
		good_plane = true;
		for (y = 0; y < t->y_sz && good_plane; y++)
			for (x = 0; x < t->x_sz && good_plane; x++)
				good_plane = sw[x][y][z];

		if (good_plane) {
			root = find_plane_mid(t, z);
			if (root)
				goto out;
		}
		if (!dz)
			continue;

		z = canonicalize(zm + dz, t->z_sz);
		good_plane = true;
		for (y = 0; y < t->y_sz && good_plane; y++)
			for (x = 0; x < t->x_sz && good_plane; x++)
				good_plane = sw[x][y][z];

		if (good_plane) {
			root = find_plane_mid(t, z);
			if (root)
				goto out;
		}
	}
	/*
	 * Note that torus-2QoS can route a torus that is missing an entire
	 * column (switches with x,y constant, for all z values) without
	 * deadlocks.
	 *
	 * if we've reached this point, we must have a column of missing
	 * switches, as routable_torus() would have returned false for
	 * any other configuration of missing switches that made it through
	 * the above.
	 *
	 * So any switch in the mid-z plane will do as the root.
	 */
	root = find_plane_mid(t, zm);
out:
	return root;
}