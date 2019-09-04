#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct proc_data {TYPE_3__* minfo; TYPE_2__* uinfo; } ;
struct mon_binlog {int dummy; } ;
struct TYPE_12__ {scalar_t__ magic; } ;
struct binlog_timepos_heap_entry {int refcnt; long long binlog_name_hash; void* writer_pid; TYPE_4__ hdr; scalar_t__ wptr; scalar_t__ rptr; } ;
struct TYPE_9__ {scalar_t__ rescan_binlog_table; } ;
struct TYPE_14__ {TYPE_1__ e_hdr; } ;
struct TYPE_13__ {int mult; long long binlog_name_hash; int binlog_data_offset; } ;
struct TYPE_11__ {int binlog_data_offset; } ;
struct TYPE_10__ {long long binlog_name_hash; } ;

/* Variables and functions */
 scalar_t__ BINLOGPOS_QUEUE_MAGIC ; 
 TYPE_8__* CData ; 
 int MES_BINLOGS_MAX ; 
 int /*<<< orphan*/ * active_pids ; 
 int active_pnum ; 
 scalar_t__ am_monitor ; 
 int /*<<< orphan*/  assert (int) ; 
 void* cdata_my_pid ; 
 struct binlog_timepos_heap_entry* conv_mon_ptr (int) ; 
 struct proc_data* get_proc_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (TYPE_5__*,TYPE_5__*,int) ; 
 TYPE_5__* mes_binlogs ; 
 int mes_binlogs_num ; 
 int mon_heap_alloc (int) ; 
 int /*<<< orphan*/  mon_heap_free (int) ; 
 int /*<<< orphan*/  set_binlog_data_offset (struct proc_data*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

int rescan_binlog_table (void) {
  int i, j, a, b, c;
  vkprintf (3, "monitor: rescanning binlog table\n");
  if (am_monitor) {
    CData->e_hdr.rescan_binlog_table = 0;
  }
  for (i = 0; i < mes_binlogs_num; i++) {
    mes_binlogs[i].mult = 0;
  }
  for (i = 0; i < active_pnum; i++) {
    struct proc_data *PData = get_proc_status (active_pids[i]);
    long long binlog_name_hash = PData->uinfo[0].binlog_name_hash;
    if (!binlog_name_hash || binlog_name_hash != PData->uinfo[1].binlog_name_hash) {
      continue;
    }
    a = -1;
    b = mes_binlogs_num;
    while (b - a > 1) {
      c = (a + b) >> 1;
      if (mes_binlogs[c].binlog_name_hash <= binlog_name_hash) {
	a = c;
      } else {
	b = c;
      }
    }
    int proc_bdata_offset = PData->minfo[0].binlog_data_offset;
    if (a >= 0 && mes_binlogs[a].binlog_name_hash == binlog_name_hash) {
      mes_binlogs[a].mult++;
      int my_bdata_offset = mes_binlogs[a].binlog_data_offset;
      if (proc_bdata_offset) {
	if (my_bdata_offset) {
	  if (my_bdata_offset != proc_bdata_offset && am_monitor) {
	    set_binlog_data_offset (PData, my_bdata_offset);
	  }
	  continue;
	}
	assert (!am_monitor);
	mes_binlogs[a].binlog_data_offset = proc_bdata_offset;
      } else if (am_monitor) {
	assert (my_bdata_offset);
	set_binlog_data_offset (PData, my_bdata_offset);
	vkprintf (3, "monitor: updating binlog info for process %d, binlog name hash %016llx to %d\n", active_pids[i], binlog_name_hash, my_bdata_offset);
      }
    } else {
      assert (mes_binlogs_num < MES_BINLOGS_MAX);
      memmove (mes_binlogs + b + 1, mes_binlogs + b, (mes_binlogs_num - b) * sizeof (struct mon_binlog));
      mes_binlogs_num++;
      mes_binlogs[b].binlog_name_hash = binlog_name_hash;
      mes_binlogs[b].mult = 1;
      if (proc_bdata_offset) {
	struct binlog_timepos_heap_entry *H = conv_mon_ptr (proc_bdata_offset);
	if (!H || H->hdr.magic != BINLOGPOS_QUEUE_MAGIC) {
	  proc_bdata_offset = 0;
	} else if (am_monitor) {
	  H->writer_pid = cdata_my_pid;
	}
      }
      mes_binlogs[b].binlog_data_offset = proc_bdata_offset;
      if (am_monitor) {
	if (!proc_bdata_offset) {
	  mes_binlogs[b].binlog_data_offset = proc_bdata_offset = mon_heap_alloc (sizeof (struct binlog_timepos_heap_entry));
	  assert (proc_bdata_offset);
	  struct binlog_timepos_heap_entry *H = conv_mon_ptr (proc_bdata_offset);
	  H->refcnt = 1;
	  H->binlog_name_hash = binlog_name_hash;
	  H->rptr = H->wptr = 0;
	  H->hdr.magic = BINLOGPOS_QUEUE_MAGIC;
	  H->writer_pid = cdata_my_pid;
	  set_binlog_data_offset (PData, proc_bdata_offset);
	  vkprintf (3, "monitor: allocating binlog info (process %d) for binlog name hash %016llx at %d\n", active_pids[i], binlog_name_hash, proc_bdata_offset);
	}
      }
    }
  }
  j = 0;
  for (i = 0; i < mes_binlogs_num; i++) {
    if (!mes_binlogs[i].mult) {
      int int_ptr = mes_binlogs[i].binlog_data_offset;
      vkprintf (3, "monitor: forgetting unused binlog name hash %016llx (data at %d)\n", mes_binlogs[i].binlog_name_hash, int_ptr);
      if (am_monitor) {
	assert (int_ptr);
	mon_heap_free (int_ptr);
      }
    } else {
      if (i != j) {
	mes_binlogs[j] = mes_binlogs[i];
      }
      j++;
    }
  }
  vkprintf (3, "monitor: %d active binlogs found\n", j);
  return mes_binlogs_num = j;
}