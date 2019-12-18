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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 scalar_t__ sigismember (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 

__attribute__((used)) static void
procstat_print_sig(const sigset_t *set, int sig, char flag)
{
	xo_emit("{d:sigmember/%c}", sigismember(set, sig) ? flag : '-');
	switch (flag) {
		case 'B':
			xo_emit("{en:mask/%s}", sigismember(set, sig) ?
			    "true" : "false");
			break;
		case 'C':
			xo_emit("{en:catch/%s}", sigismember(set, sig) ?
			    "true" : "false");
			break;
		case 'P':
			xo_emit("{en:list/%s}", sigismember(set, sig) ?
			    "true" : "false");
			break;
		case 'I':
			xo_emit("{en:ignore/%s}", sigismember(set, sig) ?
			    "true" : "false");
			break;
		default:
			xo_emit("{en:unknown/%s}", sigismember(set, sig) ?
			    "true" : "false");
			break;
	}
}