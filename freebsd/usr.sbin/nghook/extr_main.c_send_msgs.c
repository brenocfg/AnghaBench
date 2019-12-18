#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_2__ {size_t sl_cur; int /*<<< orphan*/ * sl_str; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int NgSendAsciiMsg (int,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* msgs ; 

__attribute__((used)) static void
send_msgs(int cs, const char *path)
{
	u_int	i;

	for (i = 0; i < msgs->sl_cur; i++)
		if (NgSendAsciiMsg(cs, path, "%s", msgs->sl_str[i]) == -1)
			err(EX_OSERR, "sending message '%s'", msgs->sl_str[i]);
}