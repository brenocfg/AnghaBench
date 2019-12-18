#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_int8_t ;
struct fid {int dummy; } ;
typedef  int /*<<< orphan*/  fsid_t ;
struct TYPE_6__ {int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; scalar_t__ l_pid; scalar_t__ l_len; scalar_t__ l_start; } ;
struct TYPE_5__ {scalar_t__ pid; } ;
struct TYPE_7__ {size_t lm_fh_len; scalar_t__ lm_wait; TYPE_2__ lm_fl; scalar_t__ lm_fh; TYPE_1__ lm_msg_ident; } ;
typedef  TYPE_3__ LOCKD_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int NFS_SMALLFH ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

void
show(LOCKD_MSG *mp)
{
	static char hex[] = "0123456789abcdef";
	struct fid *fidp;
	fsid_t *fsidp;
	size_t len;
	u_int8_t *p, *t, buf[NFS_SMALLFH*3+1];

	syslog(LOG_DEBUG, "process ID: %lu\n", (long)mp->lm_msg_ident.pid);

	fsidp = (fsid_t *)&mp->lm_fh;
	fidp = (struct fid *)((u_int8_t *)&mp->lm_fh + sizeof(fsid_t));

	for (t = buf, p = (u_int8_t *)mp->lm_fh,
	    len = mp->lm_fh_len;
	    len > 0; ++p, --len) {
		*t++ = '\\';
		*t++ = hex[(*p & 0xf0) >> 4];
		*t++ = hex[*p & 0x0f];
	}
	*t = '\0';

	syslog(LOG_DEBUG, "fh_len %d, fh %s\n", (int)mp->lm_fh_len, buf);

	/* Show flock structure. */
	syslog(LOG_DEBUG, "start %llu; len %llu; pid %lu; type %d; whence %d\n",
	    (unsigned long long)mp->lm_fl.l_start,
	    (unsigned long long)mp->lm_fl.l_len, (u_long)mp->lm_fl.l_pid,
	    mp->lm_fl.l_type, mp->lm_fl.l_whence);

	/* Show wait flag. */
	syslog(LOG_DEBUG, "wait was %s\n", mp->lm_wait ? "set" : "not set");
}