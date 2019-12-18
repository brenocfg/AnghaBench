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
 int DRT_VALID_FLAGS_MASK ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int db_lex (int) ; 
 int db_look_token ; 

int
db_read_token_flags(int flags)
{
	int	t;

	MPASS((flags & ~(DRT_VALID_FLAGS_MASK)) == 0);

	if (db_look_token) {
	    t = db_look_token;
	    db_look_token = 0;
	}
	else
	    t = db_lex(flags);
	return (t);
}