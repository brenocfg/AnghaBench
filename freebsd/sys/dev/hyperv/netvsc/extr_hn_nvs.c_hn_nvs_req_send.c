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
struct hn_softc {int /*<<< orphan*/  hn_prichan; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMBUS_CHANPKT_FLAG_NONE ; 
 int hn_nvs_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hn_nvs_sendctx_none ; 

__attribute__((used)) static __inline int
hn_nvs_req_send(struct hn_softc *sc, void *req, int reqlen)
{

	return (hn_nvs_send(sc->hn_prichan, VMBUS_CHANPKT_FLAG_NONE,
	    req, reqlen, &hn_nvs_sendctx_none));
}