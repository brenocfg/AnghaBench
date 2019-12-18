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
struct kinfo_vmobject {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  display_object (struct kinfo_vmobject*) ; 
 int /*<<< orphan*/  free (struct kinfo_vmobject*) ; 
 struct kinfo_vmobject* kinfo_getvmobject (int*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 
 int /*<<< orphan*/  xo_warn (char*) ; 

__attribute__((used)) static void
doobjstat(void)
{
	struct kinfo_vmobject *kvo;
	int cnt, i;

	kvo = kinfo_getvmobject(&cnt);
	if (kvo == NULL) {
		xo_warn("Failed to fetch VM object list");
		return;
	}
	xo_emit("{T:RES/%5s} {T:ACT/%5s} {T:INACT/%5s} {T:REF/%3s} {T:SHD/%3s} "
	    "{T:CM/%3s} {T:TP/%2s} {T:PATH/%s}\n");
	xo_open_list("object");
	for (i = 0; i < cnt; i++)
		display_object(&kvo[i]);
	free(kvo);
	xo_close_list("object");
}