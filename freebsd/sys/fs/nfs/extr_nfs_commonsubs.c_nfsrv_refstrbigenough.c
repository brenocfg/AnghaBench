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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  M_NFSSTRING ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NFSBCOPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfsrv_refstrbigenough(int siz, u_char **cpp, u_char **cpp2, int *slenp)
{
	u_char *cp;
	int i;

	if (siz <= *slenp)
		return;
	cp = malloc(siz + 1024, M_NFSSTRING, M_WAITOK);
	NFSBCOPY(*cpp, cp, *slenp);
	free(*cpp, M_NFSSTRING);
	i = *cpp2 - *cpp;
	*cpp = cp;
	*cpp2 = cp + i;
	*slenp = siz + 1024;
}