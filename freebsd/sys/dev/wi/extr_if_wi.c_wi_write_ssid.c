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
typedef  int /*<<< orphan*/  u_int8_t ;
struct wi_ssid {int /*<<< orphan*/  wi_ssid; int /*<<< orphan*/  wi_len; } ;
struct wi_softc {int dummy; } ;
typedef  int /*<<< orphan*/  ssid ;

/* Variables and functions */
 int ENOBUFS ; 
 int IEEE80211_NWID_LEN ; 
 int /*<<< orphan*/  htole16 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct wi_ssid*,int /*<<< orphan*/ ,int) ; 
 int wi_write_rid (struct wi_softc*,int,struct wi_ssid*,int) ; 

__attribute__((used)) static int
wi_write_ssid(struct wi_softc *sc, int rid, u_int8_t *buf, int buflen)
{
	struct wi_ssid ssid;

	if (buflen > IEEE80211_NWID_LEN)
		return ENOBUFS;
	memset(&ssid, 0, sizeof(ssid));
	ssid.wi_len = htole16(buflen);
	memcpy(ssid.wi_ssid, buf, buflen);
	return wi_write_rid(sc, rid, &ssid, sizeof(ssid));
}