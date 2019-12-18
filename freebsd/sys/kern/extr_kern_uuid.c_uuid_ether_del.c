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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ UUID_ETHER_EMPTY ; 
 scalar_t__ UUID_ETHER_UNIQUE ; 
 int UUID_NETHER ; 
 int /*<<< orphan*/  UUID_NODE_LEN ; 
 scalar_t__ bcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* uuid_ether ; 
 int /*<<< orphan*/  uuid_mutex ; 

int
uuid_ether_del(const uint8_t *addr)
{
	int i;

	mtx_lock(&uuid_mutex);
	i = 0;
	while (i < UUID_NETHER && uuid_ether[i].state == UUID_ETHER_UNIQUE &&
	    bcmp(addr, uuid_ether[i].node, UUID_NODE_LEN))
		i++;
	if (i == UUID_NETHER || uuid_ether[i].state != UUID_ETHER_UNIQUE) {
		mtx_unlock(&uuid_mutex);
		return (ENOENT);
	}

	/* Remove it by shifting higher index entries down. */
	while (i < UUID_NETHER - 1 && uuid_ether[i].state != UUID_ETHER_EMPTY) {
		uuid_ether[i] = uuid_ether[i + 1];
		i++;
	}
	if (uuid_ether[i].state != UUID_ETHER_EMPTY) {
		uuid_ether[i].state = UUID_ETHER_EMPTY;
		bzero(uuid_ether[i].node, UUID_NODE_LEN);
	}
	mtx_unlock(&uuid_mutex);
	return (0);
}