#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {char* local; } ;
struct chap {TYPE_5__ challenge; } ;
struct authinfo {TYPE_10__* physical; } ;
struct TYPE_20__ {TYPE_8__* bundle; } ;
struct TYPE_17__ {int /*<<< orphan*/  name; } ;
struct TYPE_18__ {TYPE_6__ auth; } ;
struct TYPE_12__ {scalar_t__* file; } ;
struct TYPE_13__ {TYPE_1__ cfg; } ;
struct TYPE_19__ {TYPE_7__ cfg; TYPE_2__ radius; } ;
struct TYPE_14__ {int want_authtype; } ;
struct TYPE_15__ {TYPE_3__ lcp; } ;
struct TYPE_11__ {TYPE_9__* dl; TYPE_4__ link; } ;

/* Variables and functions */
 int CHAPCHALLENGELEN ; 
 struct chap* auth2chap (struct authinfo*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  randinit () ; 
 int random () ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chap_ChallengeInit(struct authinfo *authp)
{
  struct chap *chap = auth2chap(authp);
  int len, i;
  char *cp;

  len = strlen(authp->physical->dl->bundle->cfg.auth.name);

  if (!*chap->challenge.local) {
    randinit();
    cp = chap->challenge.local;

#ifndef NORADIUS
    if (*authp->physical->dl->bundle->radius.cfg.file) {
      /* For radius, our challenge is 16 readable NUL terminated bytes :*/
      *cp++ = 16;
      for (i = 0; i < 16; i++)
        *cp++ = (random() % 10) + '0';
    } else
#endif
    {
#ifndef NODES
      if (authp->physical->link.lcp.want_authtype == 0x80)
        *cp++ = 8;	/* MS does 8 byte callenges :-/ */
      else if (authp->physical->link.lcp.want_authtype == 0x81)
        *cp++ = 16;	/* MS-CHAP-V2 does 16 bytes challenges */
      else
#endif
        *cp++ = random() % (CHAPCHALLENGELEN-16) + 16;
      for (i = 0; i < *chap->challenge.local; i++)
        *cp++ = random() & 0xff;
    }
    memcpy(cp, authp->physical->dl->bundle->cfg.auth.name, len);
  }
}