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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ssh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*,int) ; 

int
input_userauth_error(int type, u_int32_t seq, struct ssh *ssh)
{
	fatal("input_userauth_error: bad message during authentication: "
	    "type %d", type);
	return 0;
}