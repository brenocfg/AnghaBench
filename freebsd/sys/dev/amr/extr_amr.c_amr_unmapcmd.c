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
struct amr_command {int ac_flags; int /*<<< orphan*/  ac_datamap; int /*<<< orphan*/  ac_tag; int /*<<< orphan*/ * ac_data; } ;

/* Variables and functions */
 int AMR_CMD_DATAIN ; 
 int AMR_CMD_DATAOUT ; 
 int AMR_CMD_MAPPED ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static void
amr_unmapcmd(struct amr_command *ac)
{
    int			flag;

    debug_called(3);

    /* if the command involved data at all and was mapped */
    if (ac->ac_flags & AMR_CMD_MAPPED) {

	if (ac->ac_data != NULL) {

	    flag = 0;
	    if (ac->ac_flags & AMR_CMD_DATAIN)
		flag |= BUS_DMASYNC_POSTREAD;
	    if (ac->ac_flags & AMR_CMD_DATAOUT)
		flag |= BUS_DMASYNC_POSTWRITE;

	    bus_dmamap_sync(ac->ac_tag, ac->ac_datamap, flag);
	    bus_dmamap_unload(ac->ac_tag, ac->ac_datamap);
	}

	ac->ac_flags &= ~AMR_CMD_MAPPED;
    }
}