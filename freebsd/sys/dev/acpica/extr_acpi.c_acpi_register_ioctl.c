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
typedef  int /*<<< orphan*/  u_long ;
struct acpi_ioctl_hook {void* arg; int /*<<< orphan*/  fn; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  acpi_ioctl_fn ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_UNLOCK (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_ACPIDEV ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct acpi_ioctl_hook*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi ; 
 int /*<<< orphan*/  acpi_ioctl_hooks ; 
 int acpi_ioctl_hooks_initted ; 
 int /*<<< orphan*/  link ; 
 struct acpi_ioctl_hook* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
acpi_register_ioctl(u_long cmd, acpi_ioctl_fn fn, void *arg)
{
    struct acpi_ioctl_hook	*hp;

    if ((hp = malloc(sizeof(*hp), M_ACPIDEV, M_NOWAIT)) == NULL)
	return (ENOMEM);
    hp->cmd = cmd;
    hp->fn = fn;
    hp->arg = arg;

    ACPI_LOCK(acpi);
    if (acpi_ioctl_hooks_initted == 0) {
	TAILQ_INIT(&acpi_ioctl_hooks);
	acpi_ioctl_hooks_initted = 1;
    }
    TAILQ_INSERT_TAIL(&acpi_ioctl_hooks, hp, link);
    ACPI_UNLOCK(acpi);

    return (0);
}