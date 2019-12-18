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
struct gmesh {int dummy; } ;
typedef  int /*<<< orphan*/  efidp ;

/* Variables and functions */
 int ENOENT ; 
 int build_dp (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev ; 
 char* find_efi_on_zfsroot (int /*<<< orphan*/ ) ; 
 char* find_geom_efi_on_root (struct gmesh*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static int
efipart_to_dp(struct gmesh *mesh, char *path, efidp *dp)
{
	char *efimedia = NULL;
	int rv;

	efimedia = find_geom_efi_on_root(mesh);
#ifdef notyet
	if (efimedia == NULL)
		efimedia = find_efi_on_zfsroot(dev);
#endif
	if (efimedia == NULL) {
		rv = ENOENT;
		goto errout;
	}

	rv = build_dp(efimedia, path + 1, dp);
errout:
	free(efimedia);

	return rv;
}