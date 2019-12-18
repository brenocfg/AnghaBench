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
 int read (int,char*,int) ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnc (int /*<<< orphan*/ ,char*) ; 
 int write (int,char*,int) ; 

int
get_slot_number(int so)
{
    char            buf[8];
    int             rv;
    int             nslot;

    if ((rv = write(so, "S", 1)) < 1) {
	warn("write");
	goto err;
    } else if (rv != 1) {
	warnc(0, "write: fail.");
	goto err;
    }

    if ((rv = read(so, buf, sizeof buf)) < 0) {
	warn("read");
	goto err;
    }
    buf[sizeof buf - 1] = 0;
    if (sscanf(buf, "%d", &nslot) != 1) {
	warnc(0, "Invalid response.");
	goto err;
    }
    return nslot;
  err:
    return -1;
}