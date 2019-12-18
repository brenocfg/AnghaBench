#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_10__ {int /*<<< orphan*/ * mac_rpool; } ;
struct TYPE_11__ {int /*<<< orphan*/ * mci_rpool; TYPE_3__ mci_macro; int /*<<< orphan*/  mci_sasl_string; int /*<<< orphan*/  mci_tolist; int /*<<< orphan*/  mci_host; int /*<<< orphan*/  mci_heloname; int /*<<< orphan*/  mci_rstatus; int /*<<< orphan*/  mci_status; } ;
struct TYPE_9__ {int /*<<< orphan*/  nc_cname; int /*<<< orphan*/  nc_exp; } ;
struct TYPE_8__ {int /*<<< orphan*/  hs_sig; int /*<<< orphan*/  hs_exp; } ;
struct TYPE_12__ {int s_symtype; struct TYPE_12__* s_next; int /*<<< orphan*/  s_name; TYPE_4__ s_mci; TYPE_2__ s_namecanon; TYPE_1__ s_hostsig; } ;
typedef  TYPE_5__ STAB ;

/* Variables and functions */
 int /*<<< orphan*/  SM_STAB_FREE (int /*<<< orphan*/ ) ; 
 int STABSIZE ; 
#define  ST_HOSTSIG 129 
 int ST_MCI ; 
#define  ST_NAMECANON 128 
 TYPE_5__** SymTab ; 
 int /*<<< orphan*/  curtime () ; 
 int /*<<< orphan*/  sm_free (TYPE_5__*) ; 
 int /*<<< orphan*/  sm_rpool_free (int /*<<< orphan*/ *) ; 

void
rmexpstab()
{
	int i;
	STAB *s, *p, *f;
	time_t now;

	now = curtime();
	for (i = 0; i < STABSIZE; i++)
	{
		p = NULL;
		s = SymTab[i];
		while (s != NULL)
		{
			switch (s->s_symtype)
			{
			  case ST_HOSTSIG:
				if (s->s_hostsig.hs_exp >= now)
					goto next;	/* not expired */
				SM_STAB_FREE(s->s_hostsig.hs_sig); /* XXX */
				break;

			  case ST_NAMECANON:
				if (s->s_namecanon.nc_exp >= now)
					goto next;	/* not expired */
				SM_STAB_FREE(s->s_namecanon.nc_cname); /* XXX */
				break;

			  default:
				if (s->s_symtype >= ST_MCI)
				{
					/* call mci_uncache? */
					SM_STAB_FREE(s->s_mci.mci_status);
					SM_STAB_FREE(s->s_mci.mci_rstatus);
					SM_STAB_FREE(s->s_mci.mci_heloname);
#if 0
					/* not dynamically allocated */
					SM_STAB_FREE(s->s_mci.mci_host);
					SM_STAB_FREE(s->s_mci.mci_tolist);
#endif /* 0 */
#if SASL
					/* should always by NULL */
					SM_STAB_FREE(s->s_mci.mci_sasl_string);
#endif /* SASL */
					if (s->s_mci.mci_rpool != NULL)
					{
						sm_rpool_free(s->s_mci.mci_rpool);
						s->s_mci.mci_macro.mac_rpool = NULL;
						s->s_mci.mci_rpool = NULL;
					}
					break;
				}
  next:
				p = s;
				s = s->s_next;
				continue;
			}

			/* remove entry */
			SM_STAB_FREE(s->s_name); /* XXX */
			f = s;
			s = s->s_next;
			sm_free(f);	/* XXX */
			if (p == NULL)
				SymTab[i] = s;
			else
				p->s_next = s;
		}
	}
}