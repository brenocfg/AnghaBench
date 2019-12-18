#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {char* devices; int devices_done; TYPE_4__* device; } ;
typedef  TYPE_1__ KbdintAuthctxt ;
typedef  int /*<<< orphan*/  Authctxt ;

/* Variables and functions */
 int /*<<< orphan*/  auth2_method_allowed (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug2 (char*,char*) ; 
 TYPE_4__** devices ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  kbdint_reset_device (TYPE_1__*) ; 
 size_t strcspn (char*,char*) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,size_t) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static int
kbdint_next_device(Authctxt *authctxt, KbdintAuthctxt *kbdintctxt)
{
	size_t len;
	char *t;
	int i;

	if (kbdintctxt->device)
		kbdint_reset_device(kbdintctxt);
	do {
		len = kbdintctxt->devices ?
		    strcspn(kbdintctxt->devices, ",") : 0;

		if (len == 0)
			break;
		for (i = 0; devices[i]; i++) {
			if ((kbdintctxt->devices_done & (1 << i)) != 0 ||
			    !auth2_method_allowed(authctxt,
			    "keyboard-interactive", devices[i]->name))
				continue;
			if (strncmp(kbdintctxt->devices, devices[i]->name,
			    len) == 0) {
				kbdintctxt->device = devices[i];
				kbdintctxt->devices_done |= 1 << i;
			}
		}
		t = kbdintctxt->devices;
		kbdintctxt->devices = t[len] ? xstrdup(t+len+1) : NULL;
		free(t);
		debug2("kbdint_next_device: devices %s", kbdintctxt->devices ?
		    kbdintctxt->devices : "<empty>");
	} while (kbdintctxt->devices && !kbdintctxt->device);

	return kbdintctxt->device ? 1 : 0;
}