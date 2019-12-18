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
struct pcpu {int /*<<< orphan*/ * pc_device; } ;
struct cpu_device {struct pcpu* cd_pcpu; int /*<<< orphan*/  cd_rl; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * device_add_child_ordered (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct cpu_device*) ; 
 int /*<<< orphan*/  free (struct cpu_device*,int /*<<< orphan*/ ) ; 
 struct cpu_device* malloc (int,int /*<<< orphan*/ ,int) ; 
 struct pcpu* pcpu_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static device_t
cpu_add_child(device_t bus, u_int order, const char *name, int unit)
{
	struct cpu_device *cd;
	device_t child;
	struct pcpu *pc;

	if ((cd = malloc(sizeof(*cd), M_DEVBUF, M_NOWAIT | M_ZERO)) == NULL)
		return (NULL);

	resource_list_init(&cd->cd_rl);
	pc = pcpu_find(device_get_unit(bus));
	cd->cd_pcpu = pc;

	child = device_add_child_ordered(bus, order, name, unit);
	if (child != NULL) {
		pc->pc_device = child;
		device_set_ivars(child, cd);
	} else
		free(cd, M_DEVBUF);
	return (child);
}