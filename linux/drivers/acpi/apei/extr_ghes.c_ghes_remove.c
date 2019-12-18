#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct ghes {int /*<<< orphan*/  list; int /*<<< orphan*/  irq; int /*<<< orphan*/  timer; int /*<<< orphan*/  flags; struct acpi_hest_generic* generic; } ;
struct TYPE_2__ {int type; } ;
struct acpi_hest_generic {TYPE_1__ notify; } ;

/* Variables and functions */
#define  ACPI_HEST_NOTIFY_EXTERNAL 135 
#define  ACPI_HEST_NOTIFY_GPIO 134 
#define  ACPI_HEST_NOTIFY_GSIV 133 
#define  ACPI_HEST_NOTIFY_NMI 132 
#define  ACPI_HEST_NOTIFY_POLLED 131 
#define  ACPI_HEST_NOTIFY_SCI 130 
#define  ACPI_HEST_NOTIFY_SEA 129 
#define  ACPI_HEST_NOTIFY_SOFTWARE_DELEGATED 128 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  GHES_EXITING ; 
 int apei_sdei_unregister_ghes (struct ghes*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ghes*) ; 
 int /*<<< orphan*/  ghes_edac_unregister (struct ghes*) ; 
 int /*<<< orphan*/  ghes_fini (struct ghes*) ; 
 int /*<<< orphan*/  ghes_hed ; 
 int /*<<< orphan*/  ghes_list_mutex ; 
 int /*<<< orphan*/  ghes_nmi_remove (struct ghes*) ; 
 int /*<<< orphan*/  ghes_notifier_hed ; 
 int /*<<< orphan*/  ghes_sea_remove (struct ghes*) ; 
 int /*<<< orphan*/  kfree (struct ghes*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ghes* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  unregister_acpi_hed_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ghes_remove(struct platform_device *ghes_dev)
{
	int rc;
	struct ghes *ghes;
	struct acpi_hest_generic *generic;

	ghes = platform_get_drvdata(ghes_dev);
	generic = ghes->generic;

	ghes->flags |= GHES_EXITING;
	switch (generic->notify.type) {
	case ACPI_HEST_NOTIFY_POLLED:
		del_timer_sync(&ghes->timer);
		break;
	case ACPI_HEST_NOTIFY_EXTERNAL:
		free_irq(ghes->irq, ghes);
		break;

	case ACPI_HEST_NOTIFY_SCI:
	case ACPI_HEST_NOTIFY_GSIV:
	case ACPI_HEST_NOTIFY_GPIO:
		mutex_lock(&ghes_list_mutex);
		list_del_rcu(&ghes->list);
		if (list_empty(&ghes_hed))
			unregister_acpi_hed_notifier(&ghes_notifier_hed);
		mutex_unlock(&ghes_list_mutex);
		synchronize_rcu();
		break;

	case ACPI_HEST_NOTIFY_SEA:
		ghes_sea_remove(ghes);
		break;
	case ACPI_HEST_NOTIFY_NMI:
		ghes_nmi_remove(ghes);
		break;
	case ACPI_HEST_NOTIFY_SOFTWARE_DELEGATED:
		rc = apei_sdei_unregister_ghes(ghes);
		if (rc)
			return rc;
		break;
	default:
		BUG();
		break;
	}

	ghes_fini(ghes);

	ghes_edac_unregister(ghes);

	kfree(ghes);

	platform_set_drvdata(ghes_dev, NULL);

	return 0;
}