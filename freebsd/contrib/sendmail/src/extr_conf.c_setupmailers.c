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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  initerrmailers () ; 
 int /*<<< orphan*/  makemailer (char*) ; 
 int /*<<< orphan*/  sm_strlcpy (char*,char*,int) ; 

__attribute__((used)) static void
setupmailers()
{
	char buf[100];

	(void) sm_strlcpy(buf, "prog, P=/bin/sh, F=lsouDq9, T=X-Unix/X-Unix/X-Unix, A=sh -c \201u",
			sizeof(buf));
	makemailer(buf);

	(void) sm_strlcpy(buf, "*file*, P=[FILE], F=lsDFMPEouq9, T=X-Unix/X-Unix/X-Unix, A=FILE \201u",
			sizeof(buf));
	makemailer(buf);

	(void) sm_strlcpy(buf, "*include*, P=/dev/null, F=su, A=INCLUDE \201u",
			sizeof(buf));
	makemailer(buf);
	initerrmailers();
}