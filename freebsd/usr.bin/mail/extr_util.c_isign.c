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
struct ignoretab {scalar_t__ i_count; } ;
typedef  int /*<<< orphan*/  realfld ;

/* Variables and functions */
 int LINESIZE ; 
 struct ignoretab* ignoreall ; 
 int /*<<< orphan*/  istrncpy (char*,char const*,int) ; 
 int member (char*,struct ignoretab*) ; 

int
isign(const char *field, struct ignoretab ignore[2])
{
	char realfld[LINESIZE];

	if (ignore == ignoreall)
		return (1);
	/*
	 * Lower-case the string, so that "Status" and "status"
	 * will hash to the same place.
	 */
	istrncpy(realfld, field, sizeof(realfld));
	if (ignore[1].i_count > 0)
		return (!member(realfld, ignore + 1));
	else
		return (member(realfld, ignore));
}