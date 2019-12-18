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
struct TYPE_2__ {int nthreads; int /*<<< orphan*/ * result; } ;
struct section_fixture {char* name; TYPE_1__ thrd; int /*<<< orphan*/ * file; int /*<<< orphan*/ * section; } ;
struct ptunit_result {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pt_section_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptu_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ptunit_thrd_fini ; 
 int remove (char*) ; 

__attribute__((used)) static struct ptunit_result sfix_fini(struct section_fixture *sfix)
{
	char *filename;
	FILE *file;
	int thrd, errcode;

	ptu_test(ptunit_thrd_fini, &sfix->thrd);

	if (sfix->section) {
		pt_section_put(sfix->section);
		sfix->section = NULL;
	}

	filename = sfix->name;
	file = sfix->file;
	sfix->name = NULL;
	sfix->file = NULL;

	/* Try removing the file while we still have it open to avoid races
	 * with others re-using the temporary filename.
	 *
	 * On some systems that may not be possible and we can choose between:
	 *
	 *   - guaranteed leaking files or
	 *   - running the risk of removing someone elses file
	 *
	 * We choose the latter.  Assuming those systems behave consistently,
	 * removing someone elses file should only succeed if it isn't open at
	 * the moment we try removing it.  Given that this is a temporary file,
	 * we should be able to rule out accidental name clashes with
	 * non-termporary files.
	 */
	if (filename && file) {
		errcode = remove(filename);
		if (!errcode) {
			free(filename);
			filename = NULL;
		}
	}

	if (file)
		fclose(file);

	if (filename) {
		(void) remove(filename);
		free(filename);
	}

	for (thrd = 0; thrd < sfix->thrd.nthreads; ++thrd)
		ptu_int_eq(sfix->thrd.result[thrd], 0);

	return ptu_passed();
}