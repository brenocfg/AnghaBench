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
typedef  scalar_t__ u_short ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ NBTNsQuestion ;
typedef  int /*<<< orphan*/  NBTArguments ;

/* Variables and functions */
 scalar_t__ AliasHandleName (int /*<<< orphan*/ *,char*) ; 
#define  QS_TYPE_NB 129 
#define  QS_TYPE_NBSTAT 128 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static u_char  *
AliasHandleQuestion(
    u_short count,
    NBTNsQuestion * q,
    char *pmax,
    NBTArguments * nbtarg)
{

	(void)nbtarg;

	while (count != 0) {
		/* Name Filed */
		q = (NBTNsQuestion *) AliasHandleName((u_char *) q, pmax);

		if (q == NULL || (char *)(q + 1) > pmax) {
			q = NULL;
			break;
		}
		/* Type and Class filed */
		switch (ntohs(q->type)) {
		case QS_TYPE_NB:
		case QS_TYPE_NBSTAT:
			q = q + 1;
			break;
		default:
#ifdef LIBALIAS_DEBUG
			printf("\nUnknown Type on Question %0x\n", ntohs(q->type));
#endif
			break;
		}
		count--;
	}

	/* Set up to out of Question Section */
	return ((u_char *) q);
}