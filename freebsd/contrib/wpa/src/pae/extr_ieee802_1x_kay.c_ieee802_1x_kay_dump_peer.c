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
struct ieee802_1x_kay_peer {int /*<<< orphan*/  sci; int /*<<< orphan*/  mn; int /*<<< orphan*/  mi; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  mi_txt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_txt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee802_1x_kay_dump_peer(struct ieee802_1x_kay_peer *peer)
{
	wpa_printf(MSG_DEBUG, "\tMI: %s  MN: %d  SCI: %s",
		   mi_txt(peer->mi), peer->mn, sci_txt(&peer->sci));
}