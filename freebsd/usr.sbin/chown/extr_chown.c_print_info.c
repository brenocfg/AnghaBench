#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uid_t ;
typedef  scalar_t__ gid_t ;
struct TYPE_5__ {char* fts_path; TYPE_1__* fts_statp; } ;
struct TYPE_4__ {scalar_t__ st_gid; scalar_t__ st_uid; } ;
typedef  TYPE_2__ FTSENT ;

/* Variables and functions */
 scalar_t__ gid ; 
 scalar_t__ ischown ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ uid ; 

__attribute__((used)) static void
print_info(const FTSENT *p, int vflag)
{

	printf("%s", p->fts_path);
	if (vflag > 1) {
		if (ischown) {
			printf(": %ju:%ju -> %ju:%ju",
			    (uintmax_t)p->fts_statp->st_uid, 
			    (uintmax_t)p->fts_statp->st_gid,
			    (uid == (uid_t)-1) ? 
			    (uintmax_t)p->fts_statp->st_uid : (uintmax_t)uid,
			    (gid == (gid_t)-1) ? 
			    (uintmax_t)p->fts_statp->st_gid : (uintmax_t)gid);
		} else {
			printf(": %ju -> %ju", (uintmax_t)p->fts_statp->st_gid,
			    (gid == (gid_t)-1) ? 
			    (uintmax_t)p->fts_statp->st_gid : (uintmax_t)gid);
		}
	}
	printf("\n");
}