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
 int IDENT_MAIL_GIVEN ; 

__attribute__((used)) static int ident_is_sufficient(int user_ident_explicitly_given)
{
#ifndef WINDOWS
	return (user_ident_explicitly_given & IDENT_MAIL_GIVEN);
#else
	return (user_ident_explicitly_given == IDENT_ALL_GIVEN);
#endif
}