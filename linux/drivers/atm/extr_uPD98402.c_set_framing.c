#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct atm_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  C11T ; 
 int /*<<< orphan*/  C12T ; 
 int /*<<< orphan*/  C13T ; 
 int EINVAL ; 
 char const GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDR ; 
 TYPE_1__* PRIV (struct atm_dev*) ; 
 int /*<<< orphan*/  PUT (char const,int /*<<< orphan*/ ) ; 
#define  SONET_FRAME_SDH 129 
#define  SONET_FRAME_SONET 128 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 char const uPD98402_MDR_SS_MASK ; 
 char const uPD98402_MDR_SS_SHIFT ; 

__attribute__((used)) static int set_framing(struct atm_dev *dev,unsigned char framing)
{
	static const unsigned char sonet[] = { 1,2,3,0 };
	static const unsigned char sdh[] = { 1,0,0,2 };
	const char *set;
	unsigned long flags;
 
	switch (framing) {
		case SONET_FRAME_SONET:
			set = sonet;
			break;
		case SONET_FRAME_SDH:
			set = sdh;
			break;
		default:
			return -EINVAL;
	}
	spin_lock_irqsave(&PRIV(dev)->lock, flags);
	PUT(set[0],C11T);
	PUT(set[1],C12T);
	PUT(set[2],C13T);
	PUT((GET(MDR) & ~uPD98402_MDR_SS_MASK) | (set[3] <<
	    uPD98402_MDR_SS_SHIFT),MDR);
	spin_unlock_irqrestore(&PRIV(dev)->lock, flags);
	return 0;
}