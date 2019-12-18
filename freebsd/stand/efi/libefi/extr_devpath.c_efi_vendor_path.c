#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {char** VendorDefinedData; } ;
typedef  TYPE_1__ VENDOR_DEVICE_PATH_WITH_DATA ;
struct TYPE_5__ {int /*<<< orphan*/  Header; int /*<<< orphan*/  Guid; } ;
typedef  TYPE_2__ VENDOR_DEVICE_PATH ;

/* Variables and functions */
 int DevicePathNodeLength (int /*<<< orphan*/ *) ; 
 int asprintf (char**,char*,char const*,char*,...) ; 
 char* efi_make_tail (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int uuid_s_ok ; 
 int /*<<< orphan*/  uuid_to_string (int /*<<< orphan*/  const*,char**,int*) ; 

__attribute__((used)) static char *
efi_vendor_path(const char *type, VENDOR_DEVICE_PATH *node, char *suffix)
{
	uint32_t size = DevicePathNodeLength(&node->Header) - sizeof(*node);
	VENDOR_DEVICE_PATH_WITH_DATA *dp = (VENDOR_DEVICE_PATH_WITH_DATA *)node;
	char *name, *tail, *head;
	char *uuid;
	int rv;

	uuid_to_string((const uuid_t *)(void *)&node->Guid, &uuid, &rv);
	if (rv != uuid_s_ok)
		return (NULL);

	tail = efi_make_tail(suffix);
	rv = asprintf(&head, "%sVendor(%s)[%x:", type, uuid, size);
	free(uuid);
	if (rv < 0)
		return (NULL);

	if (DevicePathNodeLength(&node->Header) > sizeof(*node)) {
		for (uint32_t i = 0; i < size; i++) {
			rv = asprintf(&name, "%s%02x", head,
			    dp->VendorDefinedData[i]);
			if (rv < 0) {
				free(tail);
				free(head);
				return (NULL);
			}
			free(head);
			head = name;
		}
	}

	if (asprintf(&name, "%s]%s", head, tail) < 0)
		name = NULL;
	free(head);
	free(tail);
	return (name);
}