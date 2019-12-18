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
typedef  int /*<<< orphan*/  wpaie ;
struct ipw_wpa_ie {int /*<<< orphan*/  ie; int /*<<< orphan*/  len; } ;
struct ipw_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  IPW_CMD_SET_WPA_IE ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int ipw_cmd (struct ipw_softc*,int /*<<< orphan*/ ,struct ipw_wpa_ie*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  memset (struct ipw_wpa_ie*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ipw_setwpaie(struct ipw_softc *sc, const void *ie, int ielen)
{
	struct ipw_wpa_ie wpaie;

	memset(&wpaie, 0, sizeof(wpaie));
	wpaie.len = htole32(ielen);
	/* XXX verify length */
	memcpy(&wpaie.ie, ie, ielen);
	DPRINTF(("Setting WPA IE\n"));
	return ipw_cmd(sc, IPW_CMD_SET_WPA_IE, &wpaie, sizeof(wpaie));
}