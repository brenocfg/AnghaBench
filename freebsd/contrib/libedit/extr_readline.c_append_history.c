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
typedef  int /*<<< orphan*/  HistEvent ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  H_NSAVE_FP ; 
 char* _default_history_file () ; 
 int /*<<< orphan*/ * e ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * h ; 
 int history (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rl_initialize () ; 

int
append_history(int n, const char *filename)
{
	HistEvent ev;
	FILE *fp;

	if (h == NULL || e == NULL)
		rl_initialize();
	if (filename == NULL && (filename = _default_history_file()) == NULL)
		return errno;

	if ((fp = fopen(filename, "a")) == NULL)
		return errno;

	if (history(h, &ev, H_NSAVE_FP, (size_t)n,  fp) == -1) {
		int serrno = errno ? errno : EINVAL;
		fclose(fp);
		return serrno;
	}
	fclose(fp);
	return 0;
}