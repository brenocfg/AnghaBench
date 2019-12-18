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
struct network_packetsize_payload {scalar_t__ last_fired_bytes; int /*<<< orphan*/  payload; TYPE_1__* stats; scalar_t__ (* callback ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {scalar_t__ received_bytes; } ;

/* Variables and functions */
 int GIT_EUSER ; 
 scalar_t__ NETWORK_XFER_THRESHOLD ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int network_packetsize(size_t received, void *payload)
{
	struct network_packetsize_payload *npp = (struct network_packetsize_payload*)payload;

	/* Accumulate bytes */
	npp->stats->received_bytes += received;

	/* Fire notification if the threshold is reached */
	if ((npp->stats->received_bytes - npp->last_fired_bytes) > NETWORK_XFER_THRESHOLD) {
		npp->last_fired_bytes = npp->stats->received_bytes;

		if (npp->callback(npp->stats, npp->payload))
			return GIT_EUSER;
	}

	return 0;
}