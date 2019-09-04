#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int binlogs; int disabled; int docs; int idx_docs; int /*<<< orphan*/ * B; } ;
typedef  TYPE_1__ volume_t ;

/* Variables and functions */
 int STORAGE_ERR_UNKNOWN_VOLUME_ID ; 
 int /*<<< orphan*/  get_binlog_file_text (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* get_volume_f (long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int) ; 

int get_volume_text (char *buffer, long long volume_id) {
  int i;
  char *p = buffer;
  volume_t *V = get_volume_f (volume_id, 0);
  if (V == NULL) {
    return STORAGE_ERR_UNKNOWN_VOLUME_ID;
  }
  p += sprintf (p, "binlogs\t%d\n"
                   "disabled\t%d\n"
                   "docs\t%d\n"
                   "idx_docs\t%d\n",
    V->binlogs,
    V->disabled,
    V->docs,
    V->idx_docs
    );
  for (i = 0; i < V->binlogs; i++) {
    p += get_binlog_file_text (p, V->B[i], i + 1);
  }
  return p - buffer;
}