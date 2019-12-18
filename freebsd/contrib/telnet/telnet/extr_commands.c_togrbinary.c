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
 int /*<<< orphan*/  TELOPT_BINARY ; 
 int donebinarytoggle ; 
 scalar_t__ my_want_state_is_do (int /*<<< orphan*/ ) ; 
 scalar_t__ my_want_state_is_dont (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tel_enter_binary (int) ; 
 int /*<<< orphan*/  tel_leave_binary (int) ; 

__attribute__((used)) static int
togrbinary(int val)
{
    donebinarytoggle = 1;

    if (val == -1)
	val = my_want_state_is_do(TELOPT_BINARY) ? 0 : 1;

    if (val == 1) {
	if (my_want_state_is_do(TELOPT_BINARY)) {
	    printf("Already receiving in binary mode.\n");
	} else {
	    printf("Negotiating binary mode on input.\n");
	    tel_enter_binary(1);
	}
    } else {
	if (my_want_state_is_dont(TELOPT_BINARY)) {
	    printf("Already receiving in network ascii mode.\n");
	} else {
	    printf("Negotiating network ascii mode on input.\n");
	    tel_leave_binary(1);
	}
    }
    return 1;
}