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

/* Variables and functions */
 int ENOMEM ; 
 struct ibv_device** calloc (int,int) ; 
 int /*<<< orphan*/  count_devices ; 
 struct ibv_device** device_list ; 
 int /*<<< orphan*/  device_list_once ; 
 int errno ; 
 int num_devices ; 
 int /*<<< orphan*/  pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct ibv_device **__ibv_get_device_list(int *num)
{
	struct ibv_device **l;
	int i;

	if (num)
		*num = 0;

	pthread_once(&device_list_once, count_devices);

	if (num_devices < 0) {
		errno = -num_devices;
		return NULL;
	}

	l = calloc(num_devices + 1, sizeof (struct ibv_device *));
	if (!l) {
		errno = ENOMEM;
		return NULL;
	}

	for (i = 0; i < num_devices; ++i)
		l[i] = device_list[i];
	if (num)
		*num = num_devices;

	return l;
}