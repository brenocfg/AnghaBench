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
typedef  scalar_t__ u_int32_t ;
typedef  scalar_t__ time_t ;
struct aac_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_CLEAR_ISTATUS (struct aac_softc*,int) ; 
 int AAC_DB_SYNC_COMMAND ; 
 int AAC_GET_ISTATUS (struct aac_softc*) ; 
 scalar_t__ AAC_GET_MAILBOX (struct aac_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ AAC_IMMEDIATE_TIMEOUT ; 
 int /*<<< orphan*/  AAC_QNOTIFY (struct aac_softc*,int) ; 
 int /*<<< orphan*/  AAC_SET_MAILBOX (struct aac_softc*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ AAC_SRB_STS_SUCCESS ; 
 int EIO ; 
 char* HBA_FLAGS_DBG_ERROR_B ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static int
aac_sync_command(struct aac_softc *sc, u_int32_t command,
		 u_int32_t arg0, u_int32_t arg1, u_int32_t arg2, u_int32_t arg3,
		 u_int32_t *sp)
{
	time_t then;
	u_int32_t status;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	/* populate the mailbox */
	AAC_SET_MAILBOX(sc, command, arg0, arg1, arg2, arg3);

	/* ensure the sync command doorbell flag is cleared */
	AAC_CLEAR_ISTATUS(sc, AAC_DB_SYNC_COMMAND);

	/* then set it to signal the adapter */
	AAC_QNOTIFY(sc, AAC_DB_SYNC_COMMAND);

	/* spin waiting for the command to complete */
	then = time_uptime;
	do {
		if (time_uptime > (then + AAC_IMMEDIATE_TIMEOUT)) {
			fwprintf(sc, HBA_FLAGS_DBG_ERROR_B, "timed out");
			return(EIO);
		}
	} while (!(AAC_GET_ISTATUS(sc) & AAC_DB_SYNC_COMMAND));

	/* clear the completion flag */
	AAC_CLEAR_ISTATUS(sc, AAC_DB_SYNC_COMMAND);

	/* get the command status */
	status = AAC_GET_MAILBOX(sc, 0);
	if (sp != NULL)
		*sp = status;

	if (status != AAC_SRB_STS_SUCCESS)
		return (-1);
	return(0);
}