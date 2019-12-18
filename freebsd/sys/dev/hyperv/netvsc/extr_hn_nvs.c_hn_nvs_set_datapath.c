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
typedef  int /*<<< orphan*/  uint32_t ;
struct hn_softc {int dummy; } ;
struct hn_nvs_datapath {int /*<<< orphan*/  nvs_active_path; int /*<<< orphan*/  nvs_type; } ;
typedef  int /*<<< orphan*/  dp ;

/* Variables and functions */
 int /*<<< orphan*/  HN_NVS_TYPE_SET_DATAPATH ; 
 int /*<<< orphan*/  hn_nvs_req_send (struct hn_softc*,struct hn_nvs_datapath*,int) ; 
 int /*<<< orphan*/  memset (struct hn_nvs_datapath*,int /*<<< orphan*/ ,int) ; 

void
hn_nvs_set_datapath(struct hn_softc *sc, uint32_t path)
{
	struct hn_nvs_datapath dp;

	memset(&dp, 0, sizeof(dp));
	dp.nvs_type = HN_NVS_TYPE_SET_DATAPATH;
	dp.nvs_active_path = path;

	hn_nvs_req_send(sc, &dp, sizeof(dp));
}