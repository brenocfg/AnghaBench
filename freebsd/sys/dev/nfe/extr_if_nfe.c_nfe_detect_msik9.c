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
struct nfe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  freeenv (char*) ; 
 char* kern_getenv (char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static int
nfe_detect_msik9(struct nfe_softc *sc)
{
	static const char *maker = "MSI";
	static const char *product = "K9N6PGM2-V2 (MS-7309)";
	char *m, *p;
	int found;

	found = 0;
	m = kern_getenv("smbios.planar.maker");
	p = kern_getenv("smbios.planar.product");
	if (m != NULL && p != NULL) {
		if (strcmp(m, maker) == 0 && strcmp(p, product) == 0)
			found = 1;
	}
	if (m != NULL)
		freeenv(m);
	if (p != NULL)
		freeenv(p);

	return (found);
}