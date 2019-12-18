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
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {int /*<<< orphan*/  rdlen; } ;
typedef  int /*<<< orphan*/  NBTNsResourceNULL ;
typedef  TYPE_1__ NBTNsResource ;
typedef  int /*<<< orphan*/  NBTArguments ;

/* Variables and functions */
 scalar_t__ AliasHandleName (int /*<<< orphan*/ *,char*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_char  *
AliasHandleResourceNS(
    NBTNsResource * q,
    char *pmax,
    NBTArguments * nbtarg)
{
	NBTNsResourceNULL *n;
	u_short bcount;

	(void)nbtarg;

	if (q == NULL || (char *)(q + 1) > pmax)
		return (NULL);

	/* Forward to Resource NULL position */
	n = (NBTNsResourceNULL *) ((u_char *) q + sizeof(NBTNsResource));

	/* Check out of length */
	bcount = ntohs(q->rdlen);

	/* Resource Record Name Filed */
	q = (NBTNsResource *) AliasHandleName((u_char *) n, pmax);	/* XXX */

	if (q == NULL || (char *)((u_char *) n + bcount) > pmax)
		return (NULL);
	else
		return ((u_char *) n + bcount);
}