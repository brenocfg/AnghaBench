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
typedef  int /*<<< orphan*/  sockaddr_u ;

/* Variables and functions */
 scalar_t__ ISREFCLOCKADR (int /*<<< orphan*/ *) ; 
 scalar_t__ SOCK_UNSPEC (int /*<<< orphan*/ *) ; 
 char* refnumtoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  showhostnames ; 
 int /*<<< orphan*/  socktohost (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 
 char* trunc_left (int /*<<< orphan*/ ,size_t) ; 
 char* trunc_right (int /*<<< orphan*/ ,size_t) ; 

const char *
nntohost_col(
	sockaddr_u *	addr,
	size_t		width,
	int		preserve_lowaddrbits
	)
{
	const char *	out;

	if (!showhostnames || SOCK_UNSPEC(addr)) {
		if (preserve_lowaddrbits)
			out = trunc_left(stoa(addr), width);
		else
			out = trunc_right(stoa(addr), width);
	} else if (ISREFCLOCKADR(addr)) {
		out = refnumtoa(addr);
	} else {
		out = trunc_right(socktohost(addr), width);
	}
	return out;
}