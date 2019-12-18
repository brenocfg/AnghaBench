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
struct lcp {char* his_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogLCP ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char*) ; 

void
lcp_RecvIdentification(struct lcp *lcp, char *data)
{
  log_Printf(LogLCP, " MAGICNUM %08x\n", lcp->his_magic);
  log_Printf(LogLCP, " TEXT %s\n", data);
}