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
struct TYPE_3__ {int field; int /*<<< orphan*/  sort; } ;
typedef  TYPE_1__ GSort ;
typedef  int /*<<< orphan*/  GHolderItem ;

/* Variables and functions */
#define  SORT_BY_AVGTS 136 
#define  SORT_BY_BW 135 
#define  SORT_BY_CUMTS 134 
#define  SORT_BY_DATA 133 
#define  SORT_BY_HITS 132 
#define  SORT_BY_MAXTS 131 
#define  SORT_BY_MTHD 130 
#define  SORT_BY_PROT 129 
#define  SORT_BY_VISITORS 128 
 int /*<<< orphan*/  SORT_DESC ; 
 int /*<<< orphan*/  cmp_avgts_asc ; 
 int /*<<< orphan*/  cmp_avgts_desc ; 
 int /*<<< orphan*/  cmp_bw_asc ; 
 int /*<<< orphan*/  cmp_bw_desc ; 
 int /*<<< orphan*/  cmp_cumts_asc ; 
 int /*<<< orphan*/  cmp_cumts_desc ; 
 int /*<<< orphan*/  cmp_data_asc ; 
 int /*<<< orphan*/  cmp_data_desc ; 
 int /*<<< orphan*/  cmp_maxts_asc ; 
 int /*<<< orphan*/  cmp_maxts_desc ; 
 int /*<<< orphan*/  cmp_mthd_asc ; 
 int /*<<< orphan*/  cmp_mthd_desc ; 
 int /*<<< orphan*/  cmp_num_asc ; 
 int /*<<< orphan*/  cmp_num_desc ; 
 int /*<<< orphan*/  cmp_proto_asc ; 
 int /*<<< orphan*/  cmp_proto_desc ; 
 int /*<<< orphan*/  cmp_vis_asc ; 
 int /*<<< orphan*/  cmp_vis_desc ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

void
sort_holder_items (GHolderItem * items, int size, GSort sort)
{
  switch (sort.field) {
  case SORT_BY_HITS:
    if (sort.sort == SORT_DESC)
      qsort (items, size, sizeof (GHolderItem), cmp_num_desc);
    else
      qsort (items, size, sizeof (GHolderItem), cmp_num_asc);
    break;
  case SORT_BY_VISITORS:
    if (sort.sort == SORT_DESC)
      qsort (items, size, sizeof (GHolderItem), cmp_vis_desc);
    else
      qsort (items, size, sizeof (GHolderItem), cmp_vis_asc);
    break;
  case SORT_BY_DATA:
    if (sort.sort == SORT_DESC)
      qsort (items, size, sizeof (GHolderItem), cmp_data_desc);
    else
      qsort (items, size, sizeof (GHolderItem), cmp_data_asc);
    break;
  case SORT_BY_BW:
    if (sort.sort == SORT_DESC)
      qsort (items, size, sizeof (GHolderItem), cmp_bw_desc);
    else
      qsort (items, size, sizeof (GHolderItem), cmp_bw_asc);
    break;
  case SORT_BY_AVGTS:
    if (sort.sort == SORT_DESC)
      qsort (items, size, sizeof (GHolderItem), cmp_avgts_desc);
    else
      qsort (items, size, sizeof (GHolderItem), cmp_avgts_asc);
    break;
  case SORT_BY_CUMTS:
    if (sort.sort == SORT_DESC)
      qsort (items, size, sizeof (GHolderItem), cmp_cumts_desc);
    else
      qsort (items, size, sizeof (GHolderItem), cmp_cumts_asc);
    break;
  case SORT_BY_MAXTS:
    if (sort.sort == SORT_DESC)
      qsort (items, size, sizeof (GHolderItem), cmp_maxts_desc);
    else
      qsort (items, size, sizeof (GHolderItem), cmp_maxts_asc);
    break;
  case SORT_BY_PROT:
    if (sort.sort == SORT_DESC)
      qsort (items, size, sizeof (GHolderItem), cmp_proto_desc);
    else
      qsort (items, size, sizeof (GHolderItem), cmp_proto_asc);
    break;
  case SORT_BY_MTHD:
    if (sort.sort == SORT_DESC)
      qsort (items, size, sizeof (GHolderItem), cmp_mthd_desc);
    else
      qsort (items, size, sizeof (GHolderItem), cmp_mthd_asc);
    break;
  }
}