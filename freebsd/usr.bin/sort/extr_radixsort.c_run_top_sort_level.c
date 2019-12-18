#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sort_list_item {int dummy; } ;
struct sort_level {size_t start_position; int sln; size_t tosort_num; int leaves_num; size_t tosort; size_t sorted; int /*<<< orphan*/  leaves; struct sort_level** sublevels; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
struct TYPE_8__ {int /*<<< orphan*/  rflag; } ;
struct TYPE_5__ {int /*<<< orphan*/  rflag; } ;
struct TYPE_7__ {TYPE_1__ sm; } ;
struct TYPE_6__ {scalar_t__ complex_sort; scalar_t__ sflag; scalar_t__ kflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SORT_FUNC_RADIXSORT (int /*<<< orphan*/ ,int,int,int (*) (void const*,void const*)) ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  PTHREAD_DETACHED ; 
 TYPE_4__* default_sort_mods ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 TYPE_3__* keys ; 
 int keys_num ; 
 scalar_t__ list_coll ; 
 scalar_t__ list_coll_by_str_only ; 
 int /*<<< orphan*/  memcpy (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sort_level**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mergesort (int /*<<< orphan*/ ,int,int,int (*) (void const*,void const*)) ; 
 int /*<<< orphan*/  mtsem ; 
 int nthreads ; 
 int /*<<< orphan*/  place_item (struct sort_level*,size_t) ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_yield () ; 
 int /*<<< orphan*/  push_ls (struct sort_level*) ; 
 int /*<<< orphan*/  reverse_sort ; 
 int /*<<< orphan*/  run_sort_cycle_st () ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slsz ; 
 int /*<<< orphan*/  sort_left_dec (int) ; 
 struct sort_level** sort_malloc (int /*<<< orphan*/ ) ; 
 TYPE_2__ sort_opts_vals ; 
 int /*<<< orphan*/  sort_thread ; 

__attribute__((used)) static void
run_top_sort_level(struct sort_level *sl)
{
	struct sort_level *slc;

	reverse_sort = sort_opts_vals.kflag ? keys[0].sm.rflag :
	    default_sort_mods->rflag;

	sl->start_position = 0;
	sl->sln = 256;
	sl->sublevels = sort_malloc(slsz);
	memset(sl->sublevels, 0, slsz);

	for (size_t i = 0; i < sl->tosort_num; ++i)
		place_item(sl, i);

	if (sl->leaves_num > 1) {
		if (keys_num > 1) {
			if (sort_opts_vals.sflag) {
				mergesort(sl->leaves, sl->leaves_num,
				    sizeof(struct sort_list_item *),
				    (int(*)(const void *, const void *)) list_coll);
			} else {
				DEFAULT_SORT_FUNC_RADIXSORT(sl->leaves, sl->leaves_num,
				    sizeof(struct sort_list_item *),
				    (int(*)(const void *, const void *)) list_coll);
			}
		} else if (!sort_opts_vals.sflag && sort_opts_vals.complex_sort) {
			DEFAULT_SORT_FUNC_RADIXSORT(sl->leaves, sl->leaves_num,
			    sizeof(struct sort_list_item *),
			    (int(*)(const void *, const void *)) list_coll_by_str_only);
		}
	}

	if (!reverse_sort) {
		memcpy(sl->tosort + sl->start_position, sl->leaves,
		    sl->leaves_num * sizeof(struct sort_list_item*));
		sl->start_position += sl->leaves_num;
		sort_left_dec(sl->leaves_num);

		for (size_t i = 0; i < sl->sln; ++i) {
			slc = sl->sublevels[i];

			if (slc) {
				slc->sorted = sl->tosort;
				slc->start_position = sl->start_position;
				sl->start_position += slc->tosort_num;
				push_ls(slc);
				sl->sublevels[i] = NULL;
			}
		}

	} else {
		size_t n;

		for (size_t i = 0; i < sl->sln; ++i) {

			n = sl->sln - i - 1;
			slc = sl->sublevels[n];

			if (slc) {
				slc->sorted = sl->tosort;
				slc->start_position = sl->start_position;
				sl->start_position += slc->tosort_num;
				push_ls(slc);
				sl->sublevels[n] = NULL;
			}
		}

		memcpy(sl->tosort + sl->start_position, sl->leaves,
		    sl->leaves_num * sizeof(struct sort_list_item*));

		sort_left_dec(sl->leaves_num);
	}

#if defined(SORT_THREADS)
	if (nthreads < 2) {
#endif
		run_sort_cycle_st();
#if defined(SORT_THREADS)
	} else {
		size_t i;

		for(i = 0; i < nthreads; ++i) {
			pthread_attr_t attr;
			pthread_t pth;

			pthread_attr_init(&attr);
			pthread_attr_setdetachstate(&attr, PTHREAD_DETACHED);

			for (;;) {
				int res = pthread_create(&pth, &attr,
				    sort_thread, NULL);
				if (res >= 0)
					break;
				if (errno == EAGAIN) {
					pthread_yield();
					continue;
				}
				err(2, NULL);
			}

			pthread_attr_destroy(&attr);
		}

		for (i = 0; i < nthreads; ++i)
			sem_wait(&mtsem);
	}
#endif /* defined(SORT_THREADS) */
}