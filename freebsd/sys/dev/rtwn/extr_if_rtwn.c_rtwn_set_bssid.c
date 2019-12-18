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
typedef  int /*<<< orphan*/  uint8_t ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ R92C_BSSID (int) ; 
 int /*<<< orphan*/  le16dec (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  le32dec (int /*<<< orphan*/  const*) ; 
 int rtwn_write_2 (struct rtwn_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int rtwn_write_4 (struct rtwn_softc*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rtwn_set_bssid(struct rtwn_softc *sc, const uint8_t *bssid, int id)
{
	int error;

	error = rtwn_write_4(sc, R92C_BSSID(id), le32dec(&bssid[0]));
	if (error != 0)
		return (error);
	error = rtwn_write_2(sc, R92C_BSSID(id) + 4, le16dec(&bssid[4]));

	return (error);
}