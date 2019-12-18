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
typedef  int uint8_t ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOSPC ; 
 scalar_t__ UUID_ETHER_RANDOM ; 
 scalar_t__ UUID_ETHER_UNIQUE ; 
 int UUID_NETHER ; 
 int UUID_NODE_LEN ; 
 int /*<<< orphan*/  bcmp (int const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcopy (int const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* uuid_ether ; 
 int /*<<< orphan*/  uuid_mutex ; 

int
uuid_ether_add(const uint8_t *addr)
{
	int i, sum;

	/*
	 * Validate input. No multicast (flag 0x1), no locally administered
	 * (flag 0x2) and no 'all-zeroes' addresses.
	 */
	if (addr[0] & 0x03)
		return (EINVAL);
	sum = 0;
	for (i = 0; i < UUID_NODE_LEN; i++)
		sum += addr[i];
	if (sum == 0)
		return (EINVAL);

	mtx_lock(&uuid_mutex);

	/* Make sure the MAC isn't known already and that there's space. */
	i = 0;
	while (i < UUID_NETHER && uuid_ether[i].state == UUID_ETHER_UNIQUE) {
		if (!bcmp(addr, uuid_ether[i].node, UUID_NODE_LEN)) {
			mtx_unlock(&uuid_mutex);
			return (EEXIST);
		}
		i++;
	}
	if (i == UUID_NETHER) {
		mtx_unlock(&uuid_mutex);
		return (ENOSPC);
	}

	/* Insert MAC at index, moving the non-empty entry if possible. */
	if (uuid_ether[i].state == UUID_ETHER_RANDOM && i < UUID_NETHER - 1)
		uuid_ether[i + 1] = uuid_ether[i];
	uuid_ether[i].state = UUID_ETHER_UNIQUE;
	bcopy(addr, uuid_ether[i].node, UUID_NODE_LEN);
	mtx_unlock(&uuid_mutex);
	return (0);
}