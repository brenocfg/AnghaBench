#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bce_softc {scalar_t__ bce_chipid; } ;
struct TYPE_3__ {scalar_t__ id; int /*<<< orphan*/  prod; } ;

/* Variables and functions */
 int /*<<< orphan*/  freeenv (char*) ; 
 TYPE_1__* hs21_type_lists ; 
 char* kern_getenv (char*) ; 
 int nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
detect_hs21(struct bce_softc *bce_sc)
{
	char *sysenv;
	int found, i;

	found = 0;
	sysenv = kern_getenv("smbios.system.product");
	if (sysenv == NULL)
		return (found);
	for (i = 0; i < nitems(hs21_type_lists); i++) {
		if (bce_sc->bce_chipid == hs21_type_lists[i].id &&
		    strncmp(sysenv, hs21_type_lists[i].prod,
		    strlen(hs21_type_lists[i].prod)) == 0) {
			found++;
			break;
		}
	}
	freeenv(sysenv);
	return (found);
}