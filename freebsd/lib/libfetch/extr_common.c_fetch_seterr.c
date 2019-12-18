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
struct fetcherr {char* string; int /*<<< orphan*/  cat; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXERRSTRING ; 
 int /*<<< orphan*/  fetchLastErrCode ; 
 int /*<<< orphan*/  fetchLastErrString ; 
 struct fetcherr* fetch_finderr (struct fetcherr*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

void
fetch_seterr(struct fetcherr *p, int e)
{
	p = fetch_finderr(p, e);
	fetchLastErrCode = p->cat;
	snprintf(fetchLastErrString, MAXERRSTRING, "%s", p->string);
}