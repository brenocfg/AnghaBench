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
struct TYPE_3__ {int /*<<< orphan*/ * health; int /*<<< orphan*/ * cfg; int /*<<< orphan*/  t0a; int /*<<< orphan*/  tot_63; int /*<<< orphan*/  tot_51; int /*<<< orphan*/  valid; scalar_t__ csum; } ;
typedef  scalar_t__ CSUM ;
typedef  TYPE_1__ CFGH ;

/* Variables and functions */
 int N_SVNO_GPS ; 
 int /*<<< orphan*/  get_lsb_int16 (unsigned char**) ; 
 scalar_t__ get_lsb_short (unsigned char**) ; 
 int /*<<< orphan*/  get_mbg_cfg (unsigned char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_mbg_health (unsigned char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_mbg_tgps (unsigned char**,int /*<<< orphan*/ *) ; 

void
get_mbg_cfgh(
	unsigned char **buffpp,
	CFGH *cfghp
	)
{
  int i;

  cfghp->csum = (CSUM) get_lsb_short(buffpp);
  cfghp->valid = get_lsb_int16(buffpp);
  get_mbg_tgps(buffpp, &cfghp->tot_51);
  get_mbg_tgps(buffpp, &cfghp->tot_63);
  get_mbg_tgps(buffpp, &cfghp->t0a);

  for (i = 0; i < N_SVNO_GPS; i++)
    {
      get_mbg_cfg(buffpp, &cfghp->cfg[i]);
    }

  for (i = 0; i < N_SVNO_GPS; i++)
    {
      get_mbg_health(buffpp, &cfghp->health[i]);
    }
}