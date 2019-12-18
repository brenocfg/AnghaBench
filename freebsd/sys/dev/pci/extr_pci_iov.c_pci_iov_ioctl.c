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
typedef  int u_long ;
struct thread {int dummy; } ;
struct pci_iov_schema {int dummy; } ;
struct pci_iov_arg {int dummy; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
#define  IOV_CONFIG 130 
#define  IOV_DELETE 129 
#define  IOV_GET_SCHEMA 128 
 int pci_iov_config (struct cdev*,struct pci_iov_arg*) ; 
 int pci_iov_delete (struct cdev*) ; 
 int pci_iov_get_schema_ioctl (struct cdev*,struct pci_iov_schema*) ; 

__attribute__((used)) static int
pci_iov_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag,
    struct thread *td)
{

	switch (cmd) {
	case IOV_CONFIG:
		return (pci_iov_config(dev, (struct pci_iov_arg *)data));
	case IOV_DELETE:
		return (pci_iov_delete(dev));
	case IOV_GET_SCHEMA:
		return (pci_iov_get_schema_ioctl(dev,
		    (struct pci_iov_schema *)data));
	default:
		return (EINVAL);
	}
}