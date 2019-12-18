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

/* Variables and functions */
#define  ENOENT 129 
#define  ESRCH 128 
 char* strerror (int) ; 

char *
pfr_strerror(int errnum)
{
	switch (errnum) {
	case ESRCH:
		return "Table does not exist";
	case ENOENT:
		return "Anchor or Ruleset does not exist";
	default:
		return strerror(errnum);
	}
}