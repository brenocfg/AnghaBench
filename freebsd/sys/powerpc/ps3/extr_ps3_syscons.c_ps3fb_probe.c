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
struct vt_device {int dummy; } ;
struct ps3fb_softc {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  compatible ;

/* Variables and functions */
 int CN_DEAD ; 
 int CN_INTERNAL ; 
 int /*<<< orphan*/  OF_finddevice (char*) ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  TUNABLE_STR_FETCH (char*,char*,int) ; 
 struct ps3fb_softc ps3fb_softc ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
ps3fb_probe(struct vt_device *vd)
{
	struct ps3fb_softc *sc;
	int disable;
	char compatible[64];
	phandle_t root;

	disable = 0;
	TUNABLE_INT_FETCH("hw.syscons.disable", &disable);
	if (disable != 0)
		return (0);

	sc = &ps3fb_softc;

	TUNABLE_STR_FETCH("hw.platform", compatible, sizeof(compatible));
	if (strcmp(compatible, "ps3") == 0)
		return (CN_INTERNAL);

	root = OF_finddevice("/");
	if (OF_getprop(root, "compatible", compatible, sizeof(compatible)) <= 0)
                return (CN_DEAD);
	
	if (strncmp(compatible, "sony,ps3", sizeof(compatible)) != 0)
		return (CN_DEAD);

	return (CN_INTERNAL);
}