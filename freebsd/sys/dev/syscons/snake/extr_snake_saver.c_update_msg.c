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
struct TYPE_2__ {int /*<<< orphan*/ * ldavg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FANCY_SNAKE ; 
 int LOAD_HIGH (int /*<<< orphan*/ ) ; 
 int LOAD_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSGBUF_LEN ; 
 TYPE_1__ averunnable ; 
 int /*<<< orphan*/  message ; 
 int /*<<< orphan*/  messagelen ; 
 char* osrelease ; 
 char* ostype ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static inline void
update_msg(void)
{
	if (!FANCY_SNAKE) {
		messagelen = sprintf(message, "%s %s", ostype, osrelease);
		return;
	}
	messagelen = snprintf(message, MSGBUF_LEN,
	    "%s %s (%d.%02d %d.%02d, %d.%02d)",
	    ostype, osrelease,
	    LOAD_HIGH(averunnable.ldavg[0]), LOAD_LOW(averunnable.ldavg[0]),
	    LOAD_HIGH(averunnable.ldavg[1]), LOAD_LOW(averunnable.ldavg[1]),
	    LOAD_HIGH(averunnable.ldavg[2]), LOAD_LOW(averunnable.ldavg[2]));
}