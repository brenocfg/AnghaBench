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
struct TYPE_3__ {scalar_t__* name; int /*<<< orphan*/  tm_off; int /*<<< orphan*/  tm_on; void* offs_dl; void* offs; } ;
typedef  TYPE_1__ TZDL ;

/* Variables and functions */
 void* get_lsb_long (unsigned char**) ; 
 int /*<<< orphan*/  get_mbg_tm (unsigned char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_mbg_tzname (unsigned char**,char*) ; 

void
get_mbg_tzdl(
	unsigned char **buffpp,
	TZDL *tzdlp
	)
{
  tzdlp->offs = get_lsb_long(buffpp);
  tzdlp->offs_dl = get_lsb_long(buffpp);
  get_mbg_tm(buffpp, &tzdlp->tm_on);
  get_mbg_tm(buffpp, &tzdlp->tm_off);
  get_mbg_tzname(buffpp, (char *)tzdlp->name[0]);
  get_mbg_tzname(buffpp, (char *)tzdlp->name[1]);
}