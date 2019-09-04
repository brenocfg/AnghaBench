#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ data; scalar_t__ aio; } ;
struct TYPE_3__ {int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_use (int) ; 
 TYPE_2__* large_metafiles ; 
 TYPE_1__* large_users ; 
 int /*<<< orphan*/  metafile_free (scalar_t__,int) ; 
 int /*<<< orphan*/  metafiles_loaded ; 
 int /*<<< orphan*/  metafiles_unloaded ; 

int unload_metafile (int pos) {
  if (large_metafiles[pos].aio) {
    return 0;
  }
  if (!large_metafiles[pos].data) {
    assert (0);
    return 0;
  }
  del_use (pos);
  metafile_free (large_metafiles[pos].data, sizeof (long long) * (large_users[pos + 1].offset - large_users[pos].offset));
  large_metafiles[pos].data = 0;
  metafiles_loaded--;
  metafiles_unloaded++;
  return 1;
}