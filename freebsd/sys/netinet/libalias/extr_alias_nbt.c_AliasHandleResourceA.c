#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
typedef  int /*<<< orphan*/  u_char ;
struct in_addr {int dummy; } ;
struct TYPE_8__ {scalar_t__* uh_sum; scalar_t__ newaddr; scalar_t__ oldaddr; } ;
struct TYPE_7__ {int /*<<< orphan*/  rdlen; } ;
struct TYPE_6__ {scalar_t__ addr; } ;
typedef  TYPE_1__ NBTNsResourceA ;
typedef  TYPE_2__ NBTNsResource ;
typedef  TYPE_3__ NBTArguments ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_CHECKSUM (int,scalar_t__) ; 
 int INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  INET_NTOA_BUF (char*) ; 
 scalar_t__ SizeOfResourceA ; 
 int /*<<< orphan*/  bcmp (scalar_t__*,scalar_t__*,int) ; 
 char* inet_ntoa_r (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

__attribute__((used)) static u_char  *
AliasHandleResourceA(
    NBTNsResource * q,
    char *pmax,
    NBTArguments * nbtarg)
{
	NBTNsResourceA *a;
	u_short bcount;
#ifdef LIBALIAS_DEBUG
	char oldbuf[INET_ADDRSTRLEN];
	char newbuf[INET_ADDRSTRLEN];
#endif

	if (q == NULL || (char *)(q + 1) > pmax)
		return (NULL);

	/* Forward to Resource A position */
	a = (NBTNsResourceA *) ((u_char *) q + sizeof(NBTNsResource));

	/* Check out of length */
	bcount = ntohs(q->rdlen);

	/* Processing all in_addr array */
#ifdef LIBALIAS_DEBUG
	printf("Arec [%s->%s]",
	    inet_ntoa_r(nbtarg->oldaddr, INET_NTOA_BUF(oldbuf)),
	    inet_ntoa_r(nbtarg->newaddr, INET_NTOA_BUF(newbuf)));
#endif
	while (bcount != 0) {
		if (a == NULL || (char *)(a + 1) > pmax)
			return (NULL);
#ifdef LIBALIAS_DEBUG
		printf("..%s", inet_ntoa_r(a->addr, INET_NTOA_BUF(newbuf)));
#endif
		if (!bcmp(&nbtarg->oldaddr, &a->addr, sizeof(struct in_addr))) {
			if (*nbtarg->uh_sum != 0) {
				int acc;
				u_short *sptr;

				sptr = (u_short *) & (a->addr);	/* Old */
				acc = *sptr++;
				acc += *sptr;
				sptr = (u_short *) & nbtarg->newaddr;	/* New */
				acc -= *sptr++;
				acc -= *sptr;
				ADJUST_CHECKSUM(acc, *nbtarg->uh_sum);
			}
			a->addr = nbtarg->newaddr;
		}
		a++;		/* XXXX */
		bcount -= SizeOfResourceA;
	}
	if (a == NULL || (char *)(a + 1) > pmax)
		a = NULL;
	return ((u_char *) a);
}