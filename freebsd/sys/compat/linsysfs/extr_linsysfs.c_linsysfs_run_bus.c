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
struct scsi_host_queue {char* path; char* name; } ;
struct pfs_node {char* pn_data; } ;
struct TYPE_2__ {int bus; int slot; int func; scalar_t__ baseclass; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  char device_t ;
typedef  int /*<<< orphan*/ * devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRMN_DEV ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ PCIC_DISPLAY ; 
 scalar_t__ PCIC_STORAGE ; 
 int /*<<< orphan*/  PCI_DEV ; 
 int /*<<< orphan*/  PFS_RD ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct scsi_host_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 char* devclass_get_name (int /*<<< orphan*/ *) ; 
 int device_get_children (char,char**,int*) ; 
 int /*<<< orphan*/ * device_get_devclass (char) ; 
 struct pci_devinfo* device_get_ivars (char) ; 
 char device_get_parent (char) ; 
 int device_get_unit (char) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_number ; 
 int /*<<< orphan*/  linsysfs_fill_config ; 
 int /*<<< orphan*/  linsysfs_fill_data ; 
 int /*<<< orphan*/  linsysfs_fill_device ; 
 int /*<<< orphan*/  linsysfs_fill_revid ; 
 int /*<<< orphan*/  linsysfs_fill_subdevice ; 
 int /*<<< orphan*/  linsysfs_fill_subvendor ; 
 int /*<<< orphan*/  linsysfs_fill_uevent_drm ; 
 int /*<<< orphan*/  linsysfs_fill_uevent_pci ; 
 int /*<<< orphan*/  linsysfs_fill_vendor ; 
 int /*<<< orphan*/  linsysfs_fill_vgapci ; 
 int /*<<< orphan*/  linsysfs_link_scsi_host ; 
 int /*<<< orphan*/  linsysfs_scsiname ; 
 char* linux_driver_get_name_dev (char) ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pfs_node* pfs_create_dir (struct pfs_node*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pfs_node* pfs_create_file (struct pfs_node*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pfs_node* pfs_create_link (struct pfs_node*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_next ; 
 int /*<<< orphan*/  scsi_host_q ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
linsysfs_run_bus(device_t dev, struct pfs_node *dir, struct pfs_node *scsi,
    struct pfs_node *chardev, struct pfs_node *drm, char *path, char *prefix)
{
	struct scsi_host_queue *scsi_host;
	struct pfs_node *sub_dir, *cur_file;
	int i, nchildren, error;
	device_t *children, parent;
	devclass_t devclass;
	const char *name = NULL;
	struct pci_devinfo *dinfo;
	char *device, *host, *new_path, *devname;

	new_path = path;
	devname = malloc(16, M_TEMP, M_WAITOK);

	parent = device_get_parent(dev);
	if (parent) {
		devclass = device_get_devclass(parent);
		if (devclass != NULL)
			name = devclass_get_name(devclass);
		if (name && strcmp(name, PCI_DEV) == 0) {
			dinfo = device_get_ivars(dev);
			if (dinfo) {
				device = malloc(MAXPATHLEN, M_TEMP, M_WAITOK);
				new_path = malloc(MAXPATHLEN, M_TEMP,
				    M_WAITOK);
				new_path[0] = '\000';
				strcpy(new_path, path);
				host = malloc(MAXPATHLEN, M_TEMP, M_WAITOK);
				device[0] = '\000';
				sprintf(device, "%s:%02x:%02x.%x",
				    prefix,
				    dinfo->cfg.bus,
				    dinfo->cfg.slot,
				    dinfo->cfg.func);
				strcat(new_path, "/");
				strcat(new_path, device);
				dir = pfs_create_dir(dir, device,
				    NULL, NULL, NULL, 0);
				cur_file = pfs_create_file(dir, "vendor",
				    &linsysfs_fill_vendor, NULL, NULL, NULL,
				    PFS_RD);
				cur_file->pn_data = (void*)dev;
				cur_file = pfs_create_file(dir, "device",
				    &linsysfs_fill_device, NULL, NULL, NULL,
				    PFS_RD);
				cur_file->pn_data = (void*)dev;
				cur_file = pfs_create_file(dir,
				    "subsystem_vendor",
				    &linsysfs_fill_subvendor, NULL, NULL, NULL,
				    PFS_RD);
				cur_file->pn_data = (void*)dev;
				cur_file = pfs_create_file(dir,
				    "subsystem_device",
				    &linsysfs_fill_subdevice, NULL, NULL, NULL,
				    PFS_RD);
				cur_file->pn_data = (void*)dev;
				cur_file = pfs_create_file(dir, "revision",
				    &linsysfs_fill_revid, NULL, NULL, NULL,
				    PFS_RD);
				cur_file->pn_data = (void*)dev;
				cur_file = pfs_create_file(dir, "config",
				    &linsysfs_fill_config, NULL, NULL, NULL,
				    PFS_RD);
				cur_file->pn_data = (void*)dev;
				cur_file = pfs_create_file(dir, "uevent",
				    &linsysfs_fill_uevent_pci, NULL, NULL,
				    NULL, PFS_RD);
				cur_file->pn_data = (void*)dev;
				cur_file = pfs_create_link(dir, "subsystem",
				    &linsysfs_fill_data, NULL, NULL, NULL, 0);
				/* libdrm just checks that the link ends in "/pci" */
				cur_file->pn_data = "/sys/bus/pci";

				if (dinfo->cfg.baseclass == PCIC_STORAGE) {
					/* DJA only make this if needed */
					sprintf(host, "host%d", host_number++);
					strcat(new_path, "/");
					strcat(new_path, host);
					pfs_create_dir(dir, host,
					    NULL, NULL, NULL, 0);
					scsi_host = malloc(sizeof(
					    struct scsi_host_queue),
					    M_DEVBUF, M_NOWAIT);
					scsi_host->path = malloc(
					    strlen(new_path) + 1,
					    M_DEVBUF, M_NOWAIT);
					scsi_host->path[0] = '\000';
					bcopy(new_path, scsi_host->path,
					    strlen(new_path) + 1);
					scsi_host->name = "unknown";

					sub_dir = pfs_create_dir(scsi, host,
					    NULL, NULL, NULL, 0);
					pfs_create_link(sub_dir, "device",
					    &linsysfs_link_scsi_host,
					    NULL, NULL, NULL, 0);
					pfs_create_file(sub_dir, "proc_name",
					    &linsysfs_scsiname,
					    NULL, NULL, NULL, PFS_RD);
					scsi_host->name
					    = linux_driver_get_name_dev(dev);
					TAILQ_INSERT_TAIL(&scsi_host_q,
					    scsi_host, scsi_host_next);
				}
				free(device, M_TEMP);
				free(host, M_TEMP);
			}
		}

		devclass = device_get_devclass(dev);
		if (devclass != NULL)
			name = devclass_get_name(devclass);
		else
			name = NULL;
		if (name != NULL && strcmp(name, DRMN_DEV) == 0 &&
		    device_get_unit(dev) >= 0) {
			dinfo = device_get_ivars(parent);
			if (dinfo != NULL && dinfo->cfg.baseclass == PCIC_DISPLAY) {
				pfs_create_dir(dir, "drm", NULL, NULL, NULL, 0);
				sprintf(devname, "226:%d",
				    device_get_unit(dev));
				sub_dir = pfs_create_dir(chardev,
				    devname, NULL, NULL, NULL, 0);
				cur_file = pfs_create_link(sub_dir,
				    "device", &linsysfs_fill_vgapci, NULL,
				    NULL, NULL, PFS_RD);
				cur_file->pn_data = (void*)dir;
				cur_file = pfs_create_file(sub_dir,
				    "uevent", &linsysfs_fill_uevent_drm, NULL,
				    NULL, NULL, PFS_RD);
				cur_file->pn_data = (void*)dev;
				sprintf(devname, "card%d",
				    device_get_unit(dev));
				sub_dir = pfs_create_dir(drm,
				    devname, NULL, NULL, NULL, 0);
				cur_file = pfs_create_link(sub_dir,
				    "device", &linsysfs_fill_vgapci, NULL,
				    NULL, NULL, PFS_RD);
				cur_file->pn_data = (void*)dir;
			}
		}
	}

	error = device_get_children(dev, &children, &nchildren);
	if (error == 0) {
		for (i = 0; i < nchildren; i++)
			if (children[i])
				linsysfs_run_bus(children[i], dir, scsi,
				    chardev, drm, new_path, prefix);
		free(children, M_TEMP);
	}
	if (new_path != path)
		free(new_path, M_TEMP);
	free(devname, M_TEMP);

	return (1);
}