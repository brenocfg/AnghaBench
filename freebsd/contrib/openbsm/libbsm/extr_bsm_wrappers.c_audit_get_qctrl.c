#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct old_qctrl   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  oq ;
typedef  scalar_t__ clock_t ;
struct old_qctrl {size_t oq_hiwater; size_t oq_lowater; size_t oq_bufsz; scalar_t__ oq_delay; int oq_minfree; } ;
typedef  TYPE_1__ au_qctrl_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_GETQCTRL ; 
 int /*<<< orphan*/  A_OLDGETQCTRL ; 
 scalar_t__ EINVAL ; 
 int auditon (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ errno ; 

int
audit_get_qctrl(au_qctrl_t *qctrl, size_t sz)
{
	int ret;

	if (sizeof(*qctrl) != sz) {
		errno = EINVAL;
		return (-1);
	}

	ret = auditon(A_GETQCTRL, qctrl, sizeof(*qctrl));
#ifdef A_OLDGETQCTRL
	if ((0 != ret) && (EINVAL == errno)){
		struct old_qctrl {
			size_t   oq_hiwater;
			size_t   oq_lowater;
			size_t   oq_bufsz;
			clock_t  oq_delay;
			int	 oq_minfree;
		} oq;

		oq.oq_hiwater = (size_t)qctrl->aq_hiwater;
		oq.oq_lowater = (size_t)qctrl->aq_lowater;
		oq.oq_bufsz = (size_t)qctrl->aq_bufsz;
		oq.oq_delay = (clock_t)qctrl->aq_delay;
		oq.oq_minfree = qctrl->aq_minfree;

		ret = auditon(A_OLDGETQCTRL, &oq, sizeof(oq)); 

		qctrl->aq_hiwater = (int)oq.oq_hiwater;
		qctrl->aq_lowater = (int)oq.oq_lowater;
		qctrl->aq_bufsz = (int)oq.oq_bufsz;
		qctrl->aq_delay = (int)oq.oq_delay;
		qctrl->aq_minfree = oq.oq_minfree;
	}
#endif /* A_OLDGETQCTRL */
	return (ret);
}