#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {int len; int* ptr; int /*<<< orphan*/  extlist; int /*<<< orphan*/  chan; } ;
typedef  TYPE_1__ packet_t ;
struct TYPE_8__ {size_t* ptr; size_t len; } ;
typedef  TYPE_2__ exthdr_t ;

/* Variables and functions */
#define  BNEP_EXTENSION_CONTROL 128 
 scalar_t__ BNEP_TYPE_EXT (int) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 size_t bnep_recv_control (int /*<<< orphan*/ ,size_t*,size_t,int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  packet_adj (TYPE_1__*,size_t) ; 

__attribute__((used)) static bool
bnep_recv_extension(packet_t *pkt)
{
	exthdr_t *eh;
	size_t len, size;
	uint8_t type;

	do {
		if (pkt->len < 2)
			return false;

		type = pkt->ptr[0];
		size = pkt->ptr[1];

		if (pkt->len < size + 2)
			return false;

		switch (type) {
		case BNEP_EXTENSION_CONTROL:
			len = bnep_recv_control(pkt->chan, pkt->ptr + 2, size, true);
			if (len != size)
				log_err("ignored spurious data in exthdr");

			break;

		default:
			/* Unknown extension headers in data packets	 */
			/* SHALL be forwarded irrespective of any	 */
			/* network protocol or multicast filter settings */
			/* and any local filtering policy.		 */

			eh = malloc(sizeof(exthdr_t));
			if (eh == NULL) {
				log_err("exthdr malloc() failed: %m");
				break;
			}

			eh->ptr = pkt->ptr;
			eh->len = size;
			STAILQ_INSERT_TAIL(&pkt->extlist, eh, next);
			break;
		}

		packet_adj(pkt, size + 2);
	} while (BNEP_TYPE_EXT(type));

	return true;
}