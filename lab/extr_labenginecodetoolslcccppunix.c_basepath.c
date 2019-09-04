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
typedef  int /*<<< orphan*/  uchar ;

/* Variables and functions */
 scalar_t__ newstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

char *basepath( char *fname )
{
	char *dp = ".";
	char *p;
	if ((p = strrchr(fname, '/')) != NULL) {
		int dlen = p - fname;
		dp = (char*)newstring((uchar*)fname, dlen+1, 0);
		dp[dlen] = '\0';
	}

	return dp;
}