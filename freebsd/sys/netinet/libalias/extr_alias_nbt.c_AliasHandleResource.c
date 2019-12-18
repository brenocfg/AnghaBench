#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_8__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ NBTNsResource ;
typedef  int /*<<< orphan*/  NBTArguments ;

/* Variables and functions */
 scalar_t__ AliasHandleName (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ AliasHandleResourceA (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ AliasHandleResourceNB (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ AliasHandleResourceNBSTAT (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ AliasHandleResourceNS (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ AliasHandleResourceNULL (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
#define  RR_TYPE_A 132 
#define  RR_TYPE_NB 131 
#define  RR_TYPE_NBSTAT 130 
#define  RR_TYPE_NS 129 
#define  RR_TYPE_NULL 128 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static u_char  *
AliasHandleResource(
    u_short count,
    NBTNsResource * q,
    char *pmax,
    NBTArguments
    * nbtarg)
{
	while (count != 0) {
		/* Resource Record Name Filed */
		q = (NBTNsResource *) AliasHandleName((u_char *) q, pmax);

		if (q == NULL || (char *)(q + 1) > pmax)
			break;
#ifdef LIBALIAS_DEBUG
		printf("type=%02x, count=%d\n", ntohs(q->type), count);
#endif

		/* Type and Class filed */
		switch (ntohs(q->type)) {
		case RR_TYPE_NB:
			q = (NBTNsResource *) AliasHandleResourceNB(
			    q,
			    pmax,
			    nbtarg
			    );
			break;
		case RR_TYPE_A:
			q = (NBTNsResource *) AliasHandleResourceA(
			    q,
			    pmax,
			    nbtarg
			    );
			break;
		case RR_TYPE_NS:
			q = (NBTNsResource *) AliasHandleResourceNS(
			    q,
			    pmax,
			    nbtarg
			    );
			break;
		case RR_TYPE_NULL:
			q = (NBTNsResource *) AliasHandleResourceNULL(
			    q,
			    pmax,
			    nbtarg
			    );
			break;
		case RR_TYPE_NBSTAT:
			q = (NBTNsResource *) AliasHandleResourceNBSTAT(
			    q,
			    pmax,
			    nbtarg
			    );
			break;
		default:
#ifdef LIBALIAS_DEBUG
			printf(
			    "\nUnknown Type of Resource %0x\n",
			    ntohs(q->type)
			    );
			fflush(stdout);
#endif
			break;
		}
		count--;
	}
	return ((u_char *) q);
}