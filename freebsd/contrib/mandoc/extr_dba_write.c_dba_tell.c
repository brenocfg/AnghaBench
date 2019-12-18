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
typedef  long int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  EOVERFLOW ; 
 long INT32_MAX ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 long ftell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofp ; 

int32_t
dba_tell(void)
{
	long		 pos;

	if ((pos = ftell(ofp)) == -1)
		err(1, "ftell");
	if (pos >= INT32_MAX) {
		errno = EOVERFLOW;
		err(1, "ftell = %ld", pos);
	}
	return pos;
}