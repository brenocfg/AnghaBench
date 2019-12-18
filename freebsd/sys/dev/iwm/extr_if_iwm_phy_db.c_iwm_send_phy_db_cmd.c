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
typedef  int uint16_t ;
struct iwm_phy_db_cmd {void* length; void* type; } ;
struct iwm_phy_db {int /*<<< orphan*/  sc; } ;
struct iwm_host_cmd {int* len; int /*<<< orphan*/ * dataflags; struct iwm_phy_db_cmd** data; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_DEBUG_RESET ; 
 int /*<<< orphan*/  IWM_DPRINTF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  IWM_HCMD_DFL_NOCOPY ; 
 int /*<<< orphan*/  PHY_DB_CMD ; 
 void* htole16 (int) ; 
 int iwm_send_cmd (int /*<<< orphan*/ ,struct iwm_host_cmd*) ; 

__attribute__((used)) static int
iwm_send_phy_db_cmd(struct iwm_phy_db *phy_db, uint16_t type,
		    uint16_t length, void *data)
{
	struct iwm_phy_db_cmd phy_db_cmd;
	struct iwm_host_cmd cmd = {
		.id = PHY_DB_CMD,
	};

	IWM_DPRINTF(phy_db->sc, IWM_DEBUG_RESET,
		   "Sending PHY-DB hcmd of type %d, of length %d\n",
		   type, length);

	/* Set phy db cmd variables */
	phy_db_cmd.type = htole16(type);
	phy_db_cmd.length = htole16(length);

	/* Set hcmd variables */
	cmd.data[0] = &phy_db_cmd;
	cmd.len[0] = sizeof(struct iwm_phy_db_cmd);
	cmd.data[1] = data;
	cmd.len[1] = length;
#ifdef notyet
	cmd.dataflags[1] = IWM_HCMD_DFL_NOCOPY;
#endif

	return iwm_send_cmd(phy_db->sc, &cmd);
}