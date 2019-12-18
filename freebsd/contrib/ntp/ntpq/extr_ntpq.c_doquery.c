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
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  associd_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int doqueryex (int,int /*<<< orphan*/ ,int,size_t,char const*,int /*<<< orphan*/ *,size_t*,char const**,int /*<<< orphan*/ ) ; 

int
doquery(
	int opcode,
	associd_t associd,
	int auth,
	size_t qsize,
	const char *qdata,
	u_short *rstatus,
	size_t *rsize,
	const char **rdata
	)
{
	return doqueryex(opcode, associd, auth, qsize, qdata, rstatus,
			 rsize, rdata, FALSE);
}