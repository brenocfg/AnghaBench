#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct l_dvd_layer {int /*<<< orphan*/  end_sector_l0; int /*<<< orphan*/  end_sector; int /*<<< orphan*/  start_sector; int /*<<< orphan*/  bca; int /*<<< orphan*/  linear_density; int /*<<< orphan*/  track_density; int /*<<< orphan*/  nlayers; int /*<<< orphan*/  track_path; int /*<<< orphan*/  layer_type; int /*<<< orphan*/  disc_size; int /*<<< orphan*/  min_rate; int /*<<< orphan*/  book_type; int /*<<< orphan*/  book_version; } ;
struct dvd_struct {int format; size_t layer_num; scalar_t__ data; int /*<<< orphan*/  length; int /*<<< orphan*/  rmi; int /*<<< orphan*/  cpst; } ;
struct dvd_layer {int /*<<< orphan*/  end_sector_l0; int /*<<< orphan*/  end_sector; int /*<<< orphan*/  start_sector; int /*<<< orphan*/  bca; int /*<<< orphan*/  linear_density; int /*<<< orphan*/  track_density; int /*<<< orphan*/  nlayers; int /*<<< orphan*/  track_path; int /*<<< orphan*/  layer_type; int /*<<< orphan*/  disc_size; int /*<<< orphan*/  max_rate; int /*<<< orphan*/  book_type; int /*<<< orphan*/  book_version; } ;
struct TYPE_12__ {int /*<<< orphan*/  value; int /*<<< orphan*/  len; } ;
struct TYPE_11__ {int /*<<< orphan*/  value; int /*<<< orphan*/  len; } ;
struct TYPE_10__ {int /*<<< orphan*/  value; } ;
struct TYPE_9__ {int /*<<< orphan*/  rmi; int /*<<< orphan*/  cpst; } ;
struct TYPE_8__ {struct l_dvd_layer* layer; } ;
struct TYPE_13__ {TYPE_5__ manufact; TYPE_4__ bca; TYPE_3__ disckey; TYPE_2__ copyright; TYPE_1__ physical; } ;
typedef  TYPE_6__ l_dvd_struct ;

/* Variables and functions */
#define  DVD_STRUCT_BCA 132 
#define  DVD_STRUCT_COPYRIGHT 131 
#define  DVD_STRUCT_DISCKEY 130 
#define  DVD_STRUCT_MANUFACT 129 
#define  DVD_STRUCT_PHYSICAL 128 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct l_dvd_layer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bsd_to_linux_dvd_struct(struct dvd_struct *bp, l_dvd_struct *lp)
{
	switch (bp->format) {
	case DVD_STRUCT_PHYSICAL: {
		struct dvd_layer *blp = (struct dvd_layer *)bp->data;
		struct l_dvd_layer *llp = &lp->physical.layer[bp->layer_num];
		memset(llp, 0, sizeof(*llp));
		llp->book_version = blp->book_version;
		llp->book_type = blp->book_type;
		llp->min_rate = blp->max_rate;
		llp->disc_size = blp->disc_size;
		llp->layer_type = blp->layer_type;
		llp->track_path = blp->track_path;
		llp->nlayers = blp->nlayers;
		llp->track_density = blp->track_density;
		llp->linear_density = blp->linear_density;
		llp->bca = blp->bca;
		llp->start_sector = blp->start_sector;
		llp->end_sector = blp->end_sector;
		llp->end_sector_l0 = blp->end_sector_l0;
		break;
	}
	case DVD_STRUCT_COPYRIGHT:
		lp->copyright.cpst = bp->cpst;
		lp->copyright.rmi = bp->rmi;
		break;
	case DVD_STRUCT_DISCKEY:
		memcpy(lp->disckey.value, bp->data, sizeof(lp->disckey.value));
		break;
	case DVD_STRUCT_BCA:
		lp->bca.len = bp->length;
		memcpy(lp->bca.value, bp->data, sizeof(lp->bca.value));
		break;
	case DVD_STRUCT_MANUFACT:
		lp->manufact.len = bp->length;
		memcpy(lp->manufact.value, bp->data,
		    sizeof(lp->manufact.value));
		/* lp->manufact.layer_num is unused in Linux (redhat 7.0). */
		break;
	default:
		return (EINVAL);
	}
	return (0);
}