#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vpd_element ;
struct pcicfg_vpd {scalar_t__ vpd_reg; int vpd_rocnt; int vpd_wcnt; TYPE_2__* vpd_w; TYPE_1__* vpd_ros; struct pci_vpd_element* vpd_ident; } ;
struct pci_vpd_element {char* pve_keyword; int pve_datalen; struct pci_vpd_element* pve_data; scalar_t__ pve_flags; } ;
struct pci_list_vpd_io {size_t plvi_len; struct pci_vpd_element* plvi_data; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int len; char* keyword; struct pci_vpd_element* value; } ;
struct TYPE_3__ {int len; char* keyword; struct pci_vpd_element* value; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PVE_FLAG_IDENT ; 
 scalar_t__ PVE_FLAG_RW ; 
 struct pci_vpd_element* PVE_NEXT_LEN (struct pci_vpd_element*,int) ; 
 int copyout (struct pci_vpd_element*,struct pci_vpd_element*,int) ; 
 struct pcicfg_vpd* pci_fetch_vpd_list (int /*<<< orphan*/ ) ; 
 int strlen (struct pci_vpd_element*) ; 

__attribute__((used)) static int
pci_list_vpd(device_t dev, struct pci_list_vpd_io *lvio)
{
	struct pci_vpd_element vpd_element, *vpd_user;
	struct pcicfg_vpd *vpd;
	size_t len;
	int error, i;

	vpd = pci_fetch_vpd_list(dev);
	if (vpd->vpd_reg == 0 || vpd->vpd_ident == NULL)
		return (ENXIO);

	/*
	 * Calculate the amount of space needed in the data buffer.  An
	 * identifier element is always present followed by the read-only
	 * and read-write keywords.
	 */
	len = sizeof(struct pci_vpd_element) + strlen(vpd->vpd_ident);
	for (i = 0; i < vpd->vpd_rocnt; i++)
		len += sizeof(struct pci_vpd_element) + vpd->vpd_ros[i].len;
	for (i = 0; i < vpd->vpd_wcnt; i++)
		len += sizeof(struct pci_vpd_element) + vpd->vpd_w[i].len;

	if (lvio->plvi_len == 0) {
		lvio->plvi_len = len;
		return (0);
	}
	if (lvio->plvi_len < len) {
		lvio->plvi_len = len;
		return (ENOMEM);
	}

	/*
	 * Copyout the identifier string followed by each keyword and
	 * value.
	 */
	vpd_user = lvio->plvi_data;
	vpd_element.pve_keyword[0] = '\0';
	vpd_element.pve_keyword[1] = '\0';
	vpd_element.pve_flags = PVE_FLAG_IDENT;
	vpd_element.pve_datalen = strlen(vpd->vpd_ident);
	error = copyout(&vpd_element, vpd_user, sizeof(vpd_element));
	if (error)
		return (error);
	error = copyout(vpd->vpd_ident, vpd_user->pve_data,
	    strlen(vpd->vpd_ident));
	if (error)
		return (error);
	vpd_user = PVE_NEXT_LEN(vpd_user, vpd_element.pve_datalen);
	vpd_element.pve_flags = 0;
	for (i = 0; i < vpd->vpd_rocnt; i++) {
		vpd_element.pve_keyword[0] = vpd->vpd_ros[i].keyword[0];
		vpd_element.pve_keyword[1] = vpd->vpd_ros[i].keyword[1];
		vpd_element.pve_datalen = vpd->vpd_ros[i].len;
		error = copyout(&vpd_element, vpd_user, sizeof(vpd_element));
		if (error)
			return (error);
		error = copyout(vpd->vpd_ros[i].value, vpd_user->pve_data,
		    vpd->vpd_ros[i].len);
		if (error)
			return (error);
		vpd_user = PVE_NEXT_LEN(vpd_user, vpd_element.pve_datalen);
	}
	vpd_element.pve_flags = PVE_FLAG_RW;
	for (i = 0; i < vpd->vpd_wcnt; i++) {
		vpd_element.pve_keyword[0] = vpd->vpd_w[i].keyword[0];
		vpd_element.pve_keyword[1] = vpd->vpd_w[i].keyword[1];
		vpd_element.pve_datalen = vpd->vpd_w[i].len;
		error = copyout(&vpd_element, vpd_user, sizeof(vpd_element));
		if (error)
			return (error);
		error = copyout(vpd->vpd_w[i].value, vpd_user->pve_data,
		    vpd->vpd_w[i].len);
		if (error)
			return (error);
		vpd_user = PVE_NEXT_LEN(vpd_user, vpd_element.pve_datalen);
	}
	KASSERT((char *)vpd_user - (char *)lvio->plvi_data == len,
	    ("length mismatch"));
	lvio->plvi_len = len;
	return (0);
}