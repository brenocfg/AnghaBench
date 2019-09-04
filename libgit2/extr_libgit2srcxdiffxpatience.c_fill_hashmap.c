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
typedef  int /*<<< orphan*/  xpparam_t ;
typedef  int /*<<< orphan*/  xdfenv_t ;
struct hashmap {int alloc; struct entry* entries; int /*<<< orphan*/ * env; int /*<<< orphan*/  const* xpp; int /*<<< orphan*/ * file2; int /*<<< orphan*/ * file1; } ;
struct entry {int dummy; } ;
typedef  int /*<<< orphan*/  mmfile_t ;

/* Variables and functions */
 int /*<<< orphan*/  insert_record (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct hashmap*,int) ; 
 int /*<<< orphan*/  memset (struct entry*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xdl_malloc (int) ; 

__attribute__((used)) static int fill_hashmap(mmfile_t *file1, mmfile_t *file2,
		xpparam_t const *xpp, xdfenv_t *env,
		struct hashmap *result,
		int line1, int count1, int line2, int count2)
{
	result->file1 = file1;
	result->file2 = file2;
	result->xpp = xpp;
	result->env = env;

	/* We know exactly how large we want the hash map */
	result->alloc = count1 * 2;
	result->entries = (struct entry *)
		xdl_malloc(result->alloc * sizeof(struct entry));
	if (!result->entries)
		return -1;
	memset(result->entries, 0, result->alloc * sizeof(struct entry));

	/* First, fill with entries from the first file */
	while (count1--)
		insert_record(xpp, line1++, result, 1);

	/* Then search for matches in the second file */
	while (count2--)
		insert_record(xpp, line2++, result, 2);

	return 0;
}