#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sort_list_item {int dummy; } ;
struct sort_level {int tosort_num; int tosort_sz; struct sort_list_item** tosort; int /*<<< orphan*/  real_sln; struct sort_level** sublevels; scalar_t__ level; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct sort_level*,int /*<<< orphan*/ ,int) ; 
 struct sort_level* sort_malloc (int) ; 
 struct sort_list_item** sort_realloc (struct sort_list_item**,int) ; 

__attribute__((used)) static void
add_to_sublevel(struct sort_level *sl, struct sort_list_item *item, size_t indx)
{
	struct sort_level *ssl;

	ssl = sl->sublevels[indx];

	if (ssl == NULL) {
		ssl = sort_malloc(sizeof(struct sort_level));
		memset(ssl, 0, sizeof(struct sort_level));

		ssl->level = sl->level + 1;
		sl->sublevels[indx] = ssl;

		++(sl->real_sln);
	}

	if (++(ssl->tosort_num) > ssl->tosort_sz) {
		ssl->tosort_sz = ssl->tosort_num + 128;
		ssl->tosort = sort_realloc(ssl->tosort,
		    sizeof(struct sort_list_item*) * (ssl->tosort_sz));
	}

	ssl->tosort[ssl->tosort_num - 1] = item;
}