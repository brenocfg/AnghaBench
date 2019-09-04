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
struct string_list {int /*<<< orphan*/  nr; int /*<<< orphan*/  items; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QSORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_string_list_util_as_integral ; 
 int /*<<< orphan*/  credit_people (struct strbuf*,struct string_list*,char) ; 

__attribute__((used)) static void add_people_info(struct strbuf *out,
			    struct string_list *authors,
			    struct string_list *committers)
{
	QSORT(authors->items, authors->nr,
	      cmp_string_list_util_as_integral);
	QSORT(committers->items, committers->nr,
	      cmp_string_list_util_as_integral);

	credit_people(out, authors, 'a');
	credit_people(out, committers, 'c');
}