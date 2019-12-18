#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dvd_struct {int format; int layer_num; int /*<<< orphan*/  agid; } ;
struct TYPE_6__ {int /*<<< orphan*/  agid; } ;
struct TYPE_8__ {int layer_num; } ;
struct TYPE_7__ {int layer_num; } ;
struct TYPE_9__ {int type; TYPE_1__ disckey; TYPE_3__ copyright; TYPE_2__ physical; } ;
typedef  TYPE_4__ l_dvd_struct ;

/* Variables and functions */
#define  DVD_STRUCT_BCA 132 
#define  DVD_STRUCT_COPYRIGHT 131 
#define  DVD_STRUCT_DISCKEY 130 
#define  DVD_STRUCT_MANUFACT 129 
#define  DVD_STRUCT_PHYSICAL 128 
 int EINVAL ; 

__attribute__((used)) static int
linux_to_bsd_dvd_struct(l_dvd_struct *lp, struct dvd_struct *bp)
{
	bp->format = lp->type;
	switch (bp->format) {
	case DVD_STRUCT_PHYSICAL:
		if (bp->layer_num >= 4)
			return (EINVAL);
		bp->layer_num = lp->physical.layer_num;
		break;
	case DVD_STRUCT_COPYRIGHT:
		bp->layer_num = lp->copyright.layer_num;
		break;
	case DVD_STRUCT_DISCKEY:
		bp->agid = lp->disckey.agid;
		break;
	case DVD_STRUCT_BCA:
	case DVD_STRUCT_MANUFACT:
		break;
	default:
		return (EINVAL);
	}
	return (0);
}