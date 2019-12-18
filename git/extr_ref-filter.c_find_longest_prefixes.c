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
struct string_list {int dummy; } ;
struct strbuf {int dummy; } ;
struct argv_array {int /*<<< orphan*/  argc; int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  QSORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_pushv (struct argv_array*,char const**) ; 
 int /*<<< orphan*/  find_longest_prefixes_1 (struct string_list*,struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort_strcmp ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void find_longest_prefixes(struct string_list *out,
				  const char **patterns)
{
	struct argv_array sorted = ARGV_ARRAY_INIT;
	struct strbuf prefix = STRBUF_INIT;

	argv_array_pushv(&sorted, patterns);
	QSORT(sorted.argv, sorted.argc, qsort_strcmp);

	find_longest_prefixes_1(out, &prefix, sorted.argv, sorted.argc);

	argv_array_clear(&sorted);
	strbuf_release(&prefix);
}