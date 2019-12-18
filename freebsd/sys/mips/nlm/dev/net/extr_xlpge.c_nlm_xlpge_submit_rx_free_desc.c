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
struct nlm_xlpge_softc {int /*<<< orphan*/  rxfreeq; int /*<<< orphan*/  xlpge_dev; } ;
struct nlm_fmn_msg {scalar_t__* msg; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 void* get_buf () ; 
 int /*<<< orphan*/  memset (struct nlm_fmn_msg*,int /*<<< orphan*/ ,int) ; 
 int nlm_fmn_msgsend (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct nlm_fmn_msg*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ vtophys (void*) ; 

void
nlm_xlpge_submit_rx_free_desc(struct nlm_xlpge_softc *sc, int num)
{
	int i, size, ret, n;
	struct nlm_fmn_msg msg;
	void *ptr;

	for(i = 0; i < num; i++) {
		memset(&msg, 0, sizeof(msg));
		ptr = get_buf();
		if (!ptr) {
			device_printf(sc->xlpge_dev, "Cannot allocate mbuf\n");
			break;
		}

		msg.msg[0] = vtophys(ptr);
		if (msg.msg[0] == 0) {
			printf("Bad ptr for %p\n", ptr);
			break;
		}
		size = 1;

		n = 0;
		while (1) {
			/* on success returns 1, else 0 */
			ret = nlm_fmn_msgsend(sc->rxfreeq, size, 0, &msg);
			if (ret == 0)
				break;
			if (n++ > 10000) {
				printf("Too many credit fails for send free desc\n");
				break;
			}
		}
	}
}