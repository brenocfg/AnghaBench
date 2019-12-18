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
struct iovec {int iov_len; struct ieee80211_bpf_params* iov_base; } ;
struct ieee80211_bpf_params {int ibp_len; } ;
typedef  int /*<<< orphan*/  iov ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int writev (int,struct iovec*,int) ; 

void inject(int fd, void *buf, int buflen, struct ieee80211_bpf_params *p)
{
	struct iovec iov[2];
	int totlen;
	int rc;

	iov[0].iov_base = p;
	iov[0].iov_len = p->ibp_len;

	iov[1].iov_base = buf;
	iov[1].iov_len = buflen;
	totlen = iov[0].iov_len + iov[1].iov_len;

	rc = writev(fd, iov, sizeof(iov)/sizeof(struct iovec));
	if (rc == -1)
		err(1, "writev()");
	if (rc != totlen) {
		printf("Wrote only %d/%d\n", rc, totlen);
		exit(1);
	}
}