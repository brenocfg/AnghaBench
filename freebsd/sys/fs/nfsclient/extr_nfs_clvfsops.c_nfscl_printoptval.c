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
struct nfsmount {int dummy; } ;

/* Variables and functions */
 int snprintf (char*,size_t,char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static __inline void nfscl_printoptval(struct nfsmount *nmp, int optval,
    char *opt, char **buf, size_t *blen)
{
	int len;

	if (*blen > strlen(opt) + 1) {
		/* Could result in truncated output string. */
		len = snprintf(*buf, *blen, "%s=%d", opt, optval);
		if (len < *blen) {
			*buf += len;
			*blen -= len;
		}
	}
}