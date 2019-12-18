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
typedef  size_t uint32_t ;
struct octeon_device {size_t octeon_id; int /*<<< orphan*/  device_name; int /*<<< orphan*/  mem_access_lock; int /*<<< orphan*/  pci_win_lock; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 char* LIO_DRV_NAME ; 
 size_t LIO_MAX_DEVICES ; 
 int /*<<< orphan*/  MTX_DEF ; 
 struct octeon_device* lio_allocate_device_mem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct octeon_device** octeon_device ; 
 int /*<<< orphan*/  octeon_device_count ; 
 int /*<<< orphan*/  octeon_devices_lock ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,size_t) ; 

struct octeon_device *
lio_allocate_device(device_t device)
{
	struct octeon_device	*oct = NULL;
	uint32_t	oct_idx = 0;

	mtx_lock(&octeon_devices_lock);

	for (oct_idx = 0; oct_idx < LIO_MAX_DEVICES; oct_idx++)
		if (!octeon_device[oct_idx])
			break;

	if (oct_idx < LIO_MAX_DEVICES) {
		oct = lio_allocate_device_mem(device);
		if (oct != NULL) {
			octeon_device_count++;
			octeon_device[oct_idx] = oct;
		}
	}

	mtx_unlock(&octeon_devices_lock);

	if (oct == NULL)
		return (NULL);

	mtx_init(&oct->pci_win_lock, "pci_win_lock", NULL, MTX_DEF);
	mtx_init(&oct->mem_access_lock, "mem_access_lock", NULL, MTX_DEF);

	oct->octeon_id = oct_idx;
	snprintf(oct->device_name, sizeof(oct->device_name), "%s%d",
		 LIO_DRV_NAME, oct->octeon_id);

	return (oct);
}