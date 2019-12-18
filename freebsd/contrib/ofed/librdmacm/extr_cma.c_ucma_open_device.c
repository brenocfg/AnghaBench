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
struct ibv_device {int dummy; } ;
struct ibv_context {int dummy; } ;
typedef  scalar_t__ __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  ibv_free_device_list (struct ibv_device**) ; 
 scalar_t__ ibv_get_device_guid (struct ibv_device*) ; 
 struct ibv_device** ibv_get_device_list (int /*<<< orphan*/ *) ; 
 struct ibv_context* ibv_open_device (struct ibv_device*) ; 

__attribute__((used)) static struct ibv_context *ucma_open_device(__be64 guid)
{
	struct ibv_device **dev_list;
	struct ibv_context *verbs = NULL;
	int i;

	dev_list = ibv_get_device_list(NULL);
	if (!dev_list) {
		return NULL;
	}

	for (i = 0; dev_list[i]; i++) {
		if (ibv_get_device_guid(dev_list[i]) == guid) {
			verbs = ibv_open_device(dev_list[i]);
			break;
		}
	}

	ibv_free_device_list(dev_list);
	return verbs;
}