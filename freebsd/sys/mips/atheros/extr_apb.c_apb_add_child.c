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
typedef  int /*<<< orphan*/  u_int ;
struct apb_ivar {int /*<<< orphan*/  resources; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * device_add_child_ordered (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct apb_ivar*) ; 
 struct apb_ivar* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char const*,int) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static device_t
apb_add_child(device_t bus, u_int order, const char *name, int unit)
{
	device_t		child;
	struct apb_ivar	*ivar;

	ivar = malloc(sizeof(struct apb_ivar), M_DEVBUF, M_WAITOK | M_ZERO);
	resource_list_init(&ivar->resources);

	child = device_add_child_ordered(bus, order, name, unit);
	if (child == NULL) {
		printf("Can't add child %s%d ordered\n", name, unit);
		return (0);
	}

	device_set_ivars(child, ivar);

	return (child);
}