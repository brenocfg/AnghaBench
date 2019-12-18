#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  void* u32 ;
typedef  int u16 ;
struct mbox_cmd_log {int cursor; unsigned int size; } ;
struct mbox_cmd {scalar_t__ timestamp; int* cmd; } ;
struct cudbg_mbox_log {void** lo; void** hi; int /*<<< orphan*/  entry; } ;
struct cudbg_init {int /*<<< orphan*/  (* print ) (char*) ;scalar_t__ verbose; TYPE_3__* dbg_params; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {scalar_t__ data; void* size; } ;
struct TYPE_4__ {int mbox_cmds; struct mbox_cmd_log* log; } ;
struct TYPE_5__ {TYPE_1__ mboxlog_param; } ;
struct TYPE_6__ {TYPE_2__ u; } ;

/* Variables and functions */
 size_t CUDBG_MBOX_LOG_PARAM ; 
 int CUDBG_STATUS_ENTITY_NOT_REQUESTED ; 
 int EDOOFUS ; 
 int MBOX_LEN ; 
 int compress_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int get_scratch_buff (struct cudbg_buffer*,void*,struct cudbg_buffer*) ; 
 struct mbox_cmd* mbox_cmd_log_entry (struct mbox_cmd_log*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mbox_cmd*,int) ; 
 int /*<<< orphan*/  release_scratch_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  stub1 (char*) ; 
 int write_compression_hdr (struct cudbg_buffer*,struct cudbg_buffer*) ; 

__attribute__((used)) static int collect_mbox_log(struct cudbg_init *pdbg_init,
			    struct cudbg_buffer *dbg_buff,
			    struct cudbg_error *cudbg_err)
{
#ifdef notyet
	struct cudbg_buffer scratch_buff;
	struct cudbg_mbox_log *mboxlog = NULL;
	struct mbox_cmd_log *log = NULL;
	struct mbox_cmd *entry;
	u64 flit;
	u32 size;
	unsigned int entry_idx;
	int i, k, rc;
	u16 mbox_cmds;

	if (pdbg_init->dbg_params[CUDBG_MBOX_LOG_PARAM].u.mboxlog_param.log) {
		log = pdbg_init->dbg_params[CUDBG_MBOX_LOG_PARAM].u.
			mboxlog_param.log;
		mbox_cmds = pdbg_init->dbg_params[CUDBG_MBOX_LOG_PARAM].u.
				mboxlog_param.mbox_cmds;
	} else {
		if (pdbg_init->verbose)
			pdbg_init->print("Mbox log is not requested\n");
		return CUDBG_STATUS_ENTITY_NOT_REQUESTED;
	}

	size = sizeof(struct cudbg_mbox_log) * mbox_cmds;
	scratch_buff.size = size;
	rc = get_scratch_buff(dbg_buff, scratch_buff.size, &scratch_buff);
	if (rc)
		goto err;

	mboxlog = (struct cudbg_mbox_log *)scratch_buff.data;

	for (k = 0; k < mbox_cmds; k++) {
		entry_idx = log->cursor + k;
		if (entry_idx >= log->size)
			entry_idx -= log->size;
		entry = mbox_cmd_log_entry(log, entry_idx);

		/* skip over unused entries */
		if (entry->timestamp == 0)
			continue;

		memcpy(&mboxlog->entry, entry, sizeof(struct mbox_cmd));

		for (i = 0; i < MBOX_LEN / 8; i++) {
			flit = entry->cmd[i];
			mboxlog->hi[i] = (u32)(flit >> 32);
			mboxlog->lo[i] = (u32)flit;
		}

		mboxlog++;
	}

	rc = write_compression_hdr(&scratch_buff, dbg_buff);
	if (rc)
		goto err1;

	rc = compress_buff(&scratch_buff, dbg_buff);

err1:
	release_scratch_buff(&scratch_buff, dbg_buff);
err:
	return rc;
#endif
	return (EDOOFUS);
}