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
typedef  scalar_t__ u_int ;
struct intel_dmar_quirk_nb {scalar_t__ dev_id; scalar_t__ rev_no; int /*<<< orphan*/  (* quirk ) (struct dmar_unit*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  descr; } ;
struct intel_dmar_quirk_cpu {scalar_t__ ext_family; scalar_t__ ext_model; scalar_t__ family_code; scalar_t__ model; int stepping; int /*<<< orphan*/  (* quirk ) (struct dmar_unit*) ;int /*<<< orphan*/  descr; } ;
struct dmar_unit {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 scalar_t__ CPUID_EXT_FAMILY ; 
 scalar_t__ CPUID_EXT_MODEL ; 
 scalar_t__ CPUID_FAMILY ; 
 scalar_t__ CPUID_MODEL ; 
 scalar_t__ CPUID_STEPPING ; 
 scalar_t__ QUIRK_NB_ALL_REV ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  do_cpuid (int,scalar_t__*) ; 
 int /*<<< orphan*/ * pci_find_bsf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_get_revid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dmar_unit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct dmar_unit*) ; 

__attribute__((used)) static void
dmar_match_quirks(struct dmar_unit *dmar,
    const struct intel_dmar_quirk_nb *nb_quirks, int nb_quirks_len,
    const struct intel_dmar_quirk_cpu *cpu_quirks, int cpu_quirks_len)
{
	device_t nb;
	const struct intel_dmar_quirk_nb *nb_quirk;
	const struct intel_dmar_quirk_cpu *cpu_quirk;
	u_int p[4];
	u_int dev_id, rev_no;
	u_int ext_family, ext_model, family_code, model, stepping;
	int i;

	if (nb_quirks != NULL) {
		nb = pci_find_bsf(0, 0, 0);
		if (nb != NULL) {
			dev_id = pci_get_device(nb);
			rev_no = pci_get_revid(nb);
			for (i = 0; i < nb_quirks_len; i++) {
				nb_quirk = &nb_quirks[i];
				if (nb_quirk->dev_id == dev_id &&
				    (nb_quirk->rev_no == rev_no ||
				    nb_quirk->rev_no == QUIRK_NB_ALL_REV)) {
					if (bootverbose) {
						device_printf(dmar->dev,
						    "NB IOMMU quirk %s\n",
						    nb_quirk->descr);
					}
					nb_quirk->quirk(dmar, nb);
				}
			}
		} else {
			device_printf(dmar->dev, "cannot find northbridge\n");
		}
	}
	if (cpu_quirks != NULL) {
		do_cpuid(1, p);
		ext_family = (p[0] & CPUID_EXT_FAMILY) >> 20;
		ext_model = (p[0] & CPUID_EXT_MODEL) >> 16;
		family_code = (p[0] & CPUID_FAMILY) >> 8;
		model = (p[0] & CPUID_MODEL) >> 4;
		stepping = p[0] & CPUID_STEPPING;
		for (i = 0; i < cpu_quirks_len; i++) {
			cpu_quirk = &cpu_quirks[i];
			if (cpu_quirk->ext_family == ext_family &&
			    cpu_quirk->ext_model == ext_model &&
			    cpu_quirk->family_code == family_code &&
			    cpu_quirk->model == model &&
			    (cpu_quirk->stepping == -1 ||
			    cpu_quirk->stepping == stepping)) {
				if (bootverbose) {
					device_printf(dmar->dev,
					    "CPU IOMMU quirk %s\n",
					    cpu_quirk->descr);
				}
				cpu_quirk->quirk(dmar);
			}
		}
	}
}