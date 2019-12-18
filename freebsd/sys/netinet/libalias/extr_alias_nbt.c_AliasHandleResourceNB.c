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
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_char ;
struct in_addr {int dummy; } ;
struct TYPE_8__ {scalar_t__* uh_sum; scalar_t__ newaddr; scalar_t__ oldaddr; } ;
struct TYPE_7__ {scalar_t__ addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  rdlen; } ;
typedef  TYPE_1__ NBTNsResource ;
typedef  TYPE_2__ NBTNsRNB ;
typedef  TYPE_3__ NBTArguments ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_CHECKSUM (int,scalar_t__) ; 
 int INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  INET_NTOA_BUF (char*) ; 
 int SizeOfNsRNB ; 
 int SizeOfNsResource ; 
 int /*<<< orphan*/  bcmp (scalar_t__*,scalar_t__*,int) ; 
 char* inet_ntoa_r (scalar_t__,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static u_char  *
AliasHandleResourceNB(
    NBTNsResource * q,
    char *pmax,
    NBTArguments * nbtarg)
{
	NBTNsRNB *nb;
	u_short bcount;
#ifdef LIBALIAS_DEBUG
	char oldbuf[INET_ADDRSTRLEN];
	char newbuf[INET_ADDRSTRLEN];
#endif

	if (q == NULL || (char *)(q + 1) > pmax)
		return (NULL);
	/* Check out a length */
	bcount = ntohs(q->rdlen);

	/* Forward to Resource NB position */
	nb = (NBTNsRNB *) ((u_char *) q + SizeOfNsResource);

	/* Processing all in_addr array */
#ifdef LIBALIAS_DEBUG
	printf("NB rec[%s->%s, %dbytes] ",
	    inet_ntoa_r(nbtarg->oldaddr, INET_NTOA_BUF(oldbuf)),
	    inet_ntoa_r(nbtarg->newaddr, INET_NTOA_BUF(newbuf)),
	    bcount);
#endif
	while (nb != NULL && bcount != 0) {
		if ((char *)(nb + 1) > pmax) {
			nb = NULL;
			break;
		}
#ifdef LIBALIAS_DEBUG
		printf("<%s>", inet_ntoa_r(nb->addr, INET_NTOA_BUF(newbuf)));
#endif
		if (!bcmp(&nbtarg->oldaddr, &nb->addr, sizeof(struct in_addr))) {
			if (*nbtarg->uh_sum != 0) {
				int acc;
				u_short *sptr;

				sptr = (u_short *) & (nb->addr);
				acc = *sptr++;
				acc += *sptr;
				sptr = (u_short *) & (nbtarg->newaddr);
				acc -= *sptr++;
				acc -= *sptr;
				ADJUST_CHECKSUM(acc, *nbtarg->uh_sum);
			}
			nb->addr = nbtarg->newaddr;
#ifdef LIBALIAS_DEBUG
			printf("O");
#endif
		}
#ifdef LIBALIAS_DEBUG
		else {
			printf(".");
		}
#endif
		nb = (NBTNsRNB *) ((u_char *) nb + SizeOfNsRNB);
		bcount -= SizeOfNsRNB;
	}
	if (nb == NULL || (char *)(nb + 1) > pmax) {
		nb = NULL;
	}
	return ((u_char *) nb);
}