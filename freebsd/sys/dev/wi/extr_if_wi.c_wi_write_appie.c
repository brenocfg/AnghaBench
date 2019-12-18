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
typedef  int /*<<< orphan*/  uint16_t ;
struct wi_softc {int dummy; } ;
struct ieee80211_appie {int ie_len; int /*<<< orphan*/  ie_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  htole16 (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int wi_write_rid (struct wi_softc*,int,char*,int) ; 

__attribute__((used)) static int
wi_write_appie(struct wi_softc *sc, int rid, const struct ieee80211_appie *ie)
{
	/* NB: 42 bytes is probably ok to have on the stack */
	char buf[sizeof(uint16_t) + 40];

	if (ie->ie_len > 40)
		return EINVAL;
	/* NB: firmware requires 16-bit ie length before ie data */
	*(uint16_t *) buf = htole16(ie->ie_len);
	memcpy(buf + sizeof(uint16_t), ie->ie_data, ie->ie_len);
	return wi_write_rid(sc, rid, buf, ie->ie_len + sizeof(uint16_t));
}