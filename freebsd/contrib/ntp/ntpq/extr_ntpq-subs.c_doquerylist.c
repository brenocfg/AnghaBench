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
struct varlist {int dummy; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  associd_t ;

/* Variables and functions */
 int CTL_MAX_DATA_LEN ; 
 int doquery (int,int /*<<< orphan*/ ,int,size_t,char*,int /*<<< orphan*/ *,size_t*,char const**) ; 
 int /*<<< orphan*/  makequerydata (struct varlist*,size_t*,char*) ; 

__attribute__((used)) static int
doquerylist(
	struct varlist *vlist,
	int op,
	associd_t associd,
	int auth,
	u_short *rstatus,
	size_t *dsize,
	const char **datap
	)
{
	char data[CTL_MAX_DATA_LEN];
	size_t datalen;

	datalen = sizeof(data);
	makequerydata(vlist, &datalen, data);

	return doquery(op, associd, auth, datalen, data, rstatus, dsize,
		       datap);
}