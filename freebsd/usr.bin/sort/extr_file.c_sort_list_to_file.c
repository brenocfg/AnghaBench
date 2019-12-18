#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sort_mods {int /*<<< orphan*/  nflag; int /*<<< orphan*/  hflag; int /*<<< orphan*/  gflag; int /*<<< orphan*/  Vflag; int /*<<< orphan*/  Rflag; int /*<<< orphan*/  Mflag; } ;
struct sort_list {int /*<<< orphan*/  count; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {struct sort_mods sm; } ;
struct TYPE_3__ {int sort_method; scalar_t__ sflag; } ;

/* Variables and functions */
 int DEFAULT_SORT_ALGORITHM ; 
 int /*<<< orphan*/  DEFAULT_SORT_FUNC ; 
#define  SORT_DEFAULT 132 
#define  SORT_HEAPSORT 131 
#define  SORT_MERGESORT 130 
#define  SORT_QSORT 129 
#define  SORT_RADIXSORT 128 
 scalar_t__ byte_sort ; 
 scalar_t__ debug_sort ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 char* get_sort_method_name (int) ; 
 int /*<<< orphan*/  getstr (int) ; 
 int /*<<< orphan*/  heapsort ; 
 TYPE_2__* keys ; 
 int /*<<< orphan*/  mergesort ; 
 int /*<<< orphan*/  mt_sort (struct sort_list*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  rxsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_list_dump (struct sort_list*,char const*) ; 
 TYPE_1__ sort_opts_vals ; 
 int /*<<< orphan*/  sort_qsort ; 

void
sort_list_to_file(struct sort_list *list, const char *outfile)
{
	struct sort_mods *sm = &(keys[0].sm);

	if (!(sm->Mflag) && !(sm->Rflag) && !(sm->Vflag) && !(sm->Vflag) &&
	    !(sm->gflag) && !(sm->hflag) && !(sm->nflag)) {
		if ((sort_opts_vals.sort_method == SORT_DEFAULT) && byte_sort)
			sort_opts_vals.sort_method = SORT_RADIXSORT;

	} else if (sort_opts_vals.sort_method == SORT_RADIXSORT)
		err(2, "%s", getstr(9));

	/*
	 * to handle stable sort and the unique cases in the
	 * right order, we need stable basic algorithm
	 */
	if (sort_opts_vals.sflag) {
		switch (sort_opts_vals.sort_method){
		case SORT_MERGESORT:
			break;
		case SORT_RADIXSORT:
			break;
		case SORT_DEFAULT:
			sort_opts_vals.sort_method = SORT_MERGESORT;
			break;
		default:
			errx(2, "%s", getstr(10));
		}
	}

	if (sort_opts_vals.sort_method == SORT_DEFAULT)
		sort_opts_vals.sort_method = DEFAULT_SORT_ALGORITHM;

	if (debug_sort)
		printf("sort_method=%s\n",
		    get_sort_method_name(sort_opts_vals.sort_method));

	switch (sort_opts_vals.sort_method){
	case SORT_RADIXSORT:
		rxsort(list->list, list->count);
		sort_list_dump(list, outfile);
		break;
	case SORT_MERGESORT:
		mt_sort(list, mergesort, outfile);
		break;
	case SORT_HEAPSORT:
		mt_sort(list, heapsort,	outfile);
		break;
	case SORT_QSORT:
		mt_sort(list, sort_qsort, outfile);
		break;
	default:
		mt_sort(list, DEFAULT_SORT_FUNC, outfile);
		break;
	}
}