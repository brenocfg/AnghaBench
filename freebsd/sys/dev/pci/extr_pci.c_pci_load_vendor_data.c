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
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 char* pci_vendordata ; 
 size_t pci_vendordata_size ; 
 void* preload_fetch_addr (int /*<<< orphan*/ *) ; 
 size_t preload_fetch_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * preload_search_by_type (char*) ; 

__attribute__((used)) static void
pci_load_vendor_data(void)
{
	caddr_t data;
	void *ptr;
	size_t sz;

	data = preload_search_by_type("pci_vendor_data");
	if (data != NULL) {
		ptr = preload_fetch_addr(data);
		sz = preload_fetch_size(data);
		if (ptr != NULL && sz != 0) {
			pci_vendordata = ptr;
			pci_vendordata_size = sz;
			/* terminate the database */
			pci_vendordata[pci_vendordata_size] = '\n';
		}
	}
}