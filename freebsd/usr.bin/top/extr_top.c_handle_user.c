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
struct TYPE_2__ {int* uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_standout ; 
 scalar_t__ add_uid (int) ; 
 int /*<<< orphan*/  clear_message () ; 
 int /*<<< orphan*/  new_message (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__ ps ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ readline (char*,size_t,int) ; 
 int /*<<< orphan*/  rem_uid (int) ; 
 int /*<<< orphan*/  reset_uids () ; 
 int userid (char*) ; 

__attribute__((used)) static int
handle_user(char *buf, size_t buflen)
{
    int rc = 0;
    int uid = -1;
    char *buf2 = buf;

    new_message(MT_standout, "Username to show (+ for all): ");
    if (readline(buf, buflen, false) <= 0)
    {
	clear_message();
	return (rc);
    }

    if (buf[0] == '+' || buf[0] == '-')
    {
	if (buf[1] == '\0')
	{
	    reset_uids();
	    goto end;
	}
	else
	    ++buf2;
    }

    if ((uid = userid(buf2)) == -1)
    {
	new_message(MT_standout, " %s: unknown user", buf2);
	rc = 1;
	goto end;
    }

    if (buf2 == buf)
    {
	reset_uids();
	ps.uid[0] = uid;
	goto end;
    }

    if (buf[0] == '+')
    {
	if (add_uid(uid))
	{
	    new_message(MT_standout, " too many users, reset with '+'");
	    rc = 1;
	    goto end;
	}
    }
    else
	rem_uid(uid);

end:
    putchar('\r');
    return (rc);
}