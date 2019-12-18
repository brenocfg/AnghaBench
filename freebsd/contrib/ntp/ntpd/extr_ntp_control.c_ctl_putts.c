#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_3__ {scalar_t__ l_uf; scalar_t__ l_ui; } ;
typedef  TYPE_1__ l_fp ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  ctl_putunqstr (char const*,char*,int) ; 
 int snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctl_putts(
	const char *tag,
	l_fp *ts
	)
{
	char buffer[24];
	int  rc;

	rc = snprintf(buffer, sizeof(buffer),
		      "0x%08lx.%08lx",
		      (u_long)ts->l_ui, (u_long)ts->l_uf);
	INSIST(rc >= 0 && (size_t)rc < sizeof(buffer));
	ctl_putunqstr(tag, buffer, rc);
}