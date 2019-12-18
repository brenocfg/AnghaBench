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
typedef  int /*<<< orphan*/  u_int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_offset; int /*<<< orphan*/  svid; int /*<<< orphan*/  exclusive; } ;
struct file_lock {int nsm_status; int status; int flags; int blocking; TYPE_1__ client; int /*<<< orphan*/  filehandle; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  fhandle_t ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

void
fill_file_lock(struct file_lock *fl, const fhandle_t *fh,
    const bool_t exclusive, const int32_t svid,
    const u_int64_t offset, const u_int64_t len,
    const int state, const int status, const int flags, const int blocking)
{
	bcopy(fh, &fl->filehandle, sizeof(fhandle_t));

	fl->client.exclusive = exclusive;
	fl->client.svid = svid;
	fl->client.l_offset = offset;
	fl->client.l_len = len;

	fl->nsm_status = state;
	fl->status = status;
	fl->flags = flags;
	fl->blocking = blocking;
}