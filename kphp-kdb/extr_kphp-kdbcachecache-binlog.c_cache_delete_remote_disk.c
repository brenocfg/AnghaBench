#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ disk_id; scalar_t__ server_id; scalar_t__ node_id; } ;
union cache_packed_local_copy_location {TYPE_1__ p; int /*<<< orphan*/  i; } ;
struct lev_cache_change_disk_status {int /*<<< orphan*/  packed_location; } ;

/* Variables and functions */
 scalar_t__ dump_line_header (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  out ; 

__attribute__((used)) static int cache_delete_remote_disk (struct lev_cache_change_disk_status *E) {
  if (dump_line_header ("LEV_CACHE_DELETE_REMOTE_DISK")) {
    union cache_packed_local_copy_location u;
    u.i = E->packed_location;
    fprintf (out, "\t%d\t%d\t%d\n", (int) u.p.node_id, (int) u.p.server_id, (int) u.p.disk_id);
  }
  return 0;
}