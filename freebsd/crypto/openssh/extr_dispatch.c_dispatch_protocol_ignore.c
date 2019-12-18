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
 int /*<<< orphan*/  logit (char*,int,int /*<<< orphan*/ ) ; 

int
dispatch_protocol_ignore(int type, u_int32_t seq, struct ssh *ssh)
{
	logit("dispatch_protocol_ignore: type %d seq %u", type, seq);
	return 0;
}