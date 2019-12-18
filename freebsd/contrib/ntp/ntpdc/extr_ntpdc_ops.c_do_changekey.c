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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int32 ;
struct parse {TYPE_1__* argval; } ;
typedef  int /*<<< orphan*/  dummy ;
struct TYPE_2__ {int /*<<< orphan*/  uval; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ IMPL_XNTPD ; 
 scalar_t__ IMPL_XNTPD_OLD ; 
 int INFO_ERR_IMPL ; 
 int doquery (scalar_t__,int,int,int,int,char*,size_t*,size_t*,char const**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ impl_ver ; 

__attribute__((used)) static void
do_changekey(
	struct parse *pcmd,
	FILE *fp,
	int req
	)
{
	u_long key;
	size_t items;
	size_t itemsize;
	const char *dummy;
	int res;


	key = htonl((u_int32)pcmd->argval[0].uval);

again:
	res = doquery(impl_ver, req, 1, 1, sizeof(u_int32),
		      (char *)&key, &items, &itemsize, &dummy, 0, 
		      sizeof(dummy));
	
	if (res == INFO_ERR_IMPL && impl_ver == IMPL_XNTPD) {
		impl_ver = IMPL_XNTPD_OLD;
		goto again;
	}

	if (res == 0)
	    (void) fprintf(fp, "done!\n");
	return;
}