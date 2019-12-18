#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct reset_flags {int /*<<< orphan*/  flags; } ;
struct parse {size_t nargs; TYPE_1__* argval; } ;
struct TYPE_4__ {int /*<<< orphan*/  flag; int /*<<< orphan*/  str; } ;
struct TYPE_3__ {char* string; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ IMPL_XNTPD ; 
 scalar_t__ IMPL_XNTPD_OLD ; 
 size_t INFO_ERR_IMPL ; 
 int /*<<< orphan*/  REQ_RESET_STATS ; 
 scalar_t__ STREQ (char*,int /*<<< orphan*/ ) ; 
 size_t doquery (scalar_t__,int /*<<< orphan*/ ,int,int,int,char*,size_t*,size_t*,char const**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ impl_ver ; 
 TYPE_2__* sreset ; 

__attribute__((used)) static void
reset(
	struct parse *pcmd,
	FILE *fp
	)
{
	struct reset_flags rflags;
	size_t items;
	size_t itemsize;
	const char *dummy;
	int i;
	size_t res;
	int err;

	err = 0;
	rflags.flags = 0;
	for (res = 0; res < pcmd->nargs; res++) {
		for (i = 0; sreset[i].flag != 0; i++) {
			if (STREQ(pcmd->argval[res].string, sreset[i].str))
				break;
		}
		if (sreset[i].flag == 0) {
			fprintf(fp, "Flag %s unknown\n",
				pcmd->argval[res].string);
			err = 1;
		} else {
			rflags.flags |= sreset[i].flag;
		}
	}
	rflags.flags = htonl(rflags.flags);

	if (err) {
		(void) fprintf(fp, "Not done due to errors\n");
		return;
	}

again:
	res = doquery(impl_ver, REQ_RESET_STATS, 1, 1,
		      sizeof(struct reset_flags), (char *)&rflags, &items,
		      &itemsize, &dummy, 0, sizeof(struct reset_flags));
	
	if (res == INFO_ERR_IMPL && impl_ver == IMPL_XNTPD) {
		impl_ver = IMPL_XNTPD_OLD;
		goto again;
	}

	if (res == 0)
	    (void) fprintf(fp, "done!\n");
	return;
}