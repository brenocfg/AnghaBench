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
typedef  int /*<<< orphan*/  uint16_t ;
struct iwm_softc {int dummy; } ;
struct iwm_host_cmd {int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int iwm_mvm_send_cmd_status (struct iwm_softc*,struct iwm_host_cmd*,int /*<<< orphan*/ *) ; 

int
iwm_mvm_send_cmd_pdu_status(struct iwm_softc *sc, uint32_t id,
	uint16_t len, const void *data, uint32_t *status)
{
	struct iwm_host_cmd cmd = {
		.id = id,
		.len = { len, },
		.data = { data, },
	};

	return iwm_mvm_send_cmd_status(sc, &cmd, status);
}