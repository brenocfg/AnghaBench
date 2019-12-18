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
struct ptunit_suite {int dummy; } ;
struct image_fixture {void* fini; int /*<<< orphan*/ * init; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_cached ; 
 int /*<<< orphan*/  add_cached_bad_isid ; 
 int /*<<< orphan*/  add_cached_null ; 
 int /*<<< orphan*/  add_cached_null_asid ; 
 int /*<<< orphan*/  add_cached_twice ; 
 int /*<<< orphan*/  adjacent ; 
 int /*<<< orphan*/  contained ; 
 int /*<<< orphan*/  contained_back ; 
 int /*<<< orphan*/  contained_multiple ; 
 int /*<<< orphan*/  copy ; 
 int /*<<< orphan*/  copy_empty ; 
 int /*<<< orphan*/  copy_merge ; 
 int /*<<< orphan*/  copy_overlap ; 
 int /*<<< orphan*/  copy_replace ; 
 int /*<<< orphan*/  copy_self ; 
 int /*<<< orphan*/  copy_shrink ; 
 int /*<<< orphan*/  copy_split ; 
 void* dfix_fini ; 
 int /*<<< orphan*/  find ; 
 int /*<<< orphan*/  find_asid ; 
 int /*<<< orphan*/  find_bad_asid ; 
 int /*<<< orphan*/  find_nomem ; 
 int /*<<< orphan*/  find_null ; 
 int /*<<< orphan*/  fini ; 
 int /*<<< orphan*/  fini_empty ; 
 int /*<<< orphan*/  fini_null ; 
 void* ifix_fini ; 
 int /*<<< orphan*/ * ifix_init ; 
 int /*<<< orphan*/  init ; 
 int /*<<< orphan*/  init_name ; 
 int /*<<< orphan*/  init_null ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  name_none ; 
 int /*<<< orphan*/  name_null ; 
 int /*<<< orphan*/  overlap_back ; 
 int /*<<< orphan*/  overlap_front ; 
 int /*<<< orphan*/  overlap_mid ; 
 int /*<<< orphan*/  overlap_multiple ; 
 int /*<<< orphan*/  ptu_run (struct ptunit_suite,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_run_f (struct ptunit_suite,int /*<<< orphan*/ ,struct image_fixture) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 
 int /*<<< orphan*/  read ; 
 int /*<<< orphan*/  read_asid ; 
 int /*<<< orphan*/  read_bad_asid ; 
 int /*<<< orphan*/  read_callback ; 
 int /*<<< orphan*/  read_empty ; 
 int /*<<< orphan*/  read_error ; 
 int /*<<< orphan*/  read_nomem ; 
 int /*<<< orphan*/  read_null ; 
 int /*<<< orphan*/  read_null_asid ; 
 int /*<<< orphan*/  read_spurious_error ; 
 int /*<<< orphan*/  read_truncated ; 
 int /*<<< orphan*/  remove_all_by_filename ; 
 int /*<<< orphan*/  remove_bad_asid ; 
 int /*<<< orphan*/  remove_bad_vaddr ; 
 int /*<<< orphan*/  remove_by_asid ; 
 int /*<<< orphan*/  remove_by_filename ; 
 int /*<<< orphan*/  remove_by_filename_bad_asid ; 
 int /*<<< orphan*/  remove_none_by_filename ; 
 int /*<<< orphan*/  remove_section ; 
 int /*<<< orphan*/ * rfix_init ; 
 int /*<<< orphan*/  same ; 
 int /*<<< orphan*/  same_different_isid ; 
 int /*<<< orphan*/  same_different_offset ; 
 int /*<<< orphan*/  validate ; 
 int /*<<< orphan*/  validate_bad_asid ; 
 int /*<<< orphan*/  validate_bad_isid ; 
 int /*<<< orphan*/  validate_bad_offset ; 
 int /*<<< orphan*/  validate_bad_size ; 
 int /*<<< orphan*/  validate_bad_vaddr ; 
 int /*<<< orphan*/  validate_null ; 

int main(int argc, char **argv)
{
	struct image_fixture dfix, ifix, rfix;
	struct ptunit_suite suite;

	/* Dfix provides image destruction. */
	dfix.init = NULL;
	dfix.fini = dfix_fini;

	/* Ifix provides an empty image. */
	ifix.init = ifix_init;
	ifix.fini = ifix_fini;

	/* Rfix provides an image with two sections added. */
	rfix.init = rfix_init;
	rfix.fini = ifix_fini;

	suite = ptunit_mk_suite(argc, argv);

	ptu_run(suite, init);
	ptu_run_f(suite, init_name, dfix);
	ptu_run(suite, init_null);

	ptu_run(suite, fini);
	ptu_run(suite, fini_empty);
	ptu_run(suite, fini_null);

	ptu_run_f(suite, name, dfix);
	ptu_run(suite, name_none);
	ptu_run(suite, name_null);

	ptu_run_f(suite, read_empty, ifix);
	ptu_run_f(suite, overlap_front, ifix);
	ptu_run_f(suite, overlap_back, ifix);
	ptu_run_f(suite, overlap_multiple, ifix);
	ptu_run_f(suite, overlap_mid, ifix);
	ptu_run_f(suite, contained, ifix);
	ptu_run_f(suite, contained_multiple, ifix);
	ptu_run_f(suite, contained_back, ifix);
	ptu_run_f(suite, same, ifix);
	ptu_run_f(suite, same_different_isid, ifix);
	ptu_run_f(suite, same_different_offset, ifix);
	ptu_run_f(suite, adjacent, ifix);

	ptu_run_f(suite, read_null, rfix);
	ptu_run_f(suite, read, rfix);
	ptu_run_f(suite, read_null, rfix);
	ptu_run_f(suite, read_asid, ifix);
	ptu_run_f(suite, read_bad_asid, rfix);
	ptu_run_f(suite, read_null_asid, rfix);
	ptu_run_f(suite, read_callback, rfix);
	ptu_run_f(suite, read_nomem, rfix);
	ptu_run_f(suite, read_truncated, rfix);
	ptu_run_f(suite, read_error, rfix);
	ptu_run_f(suite, read_spurious_error, rfix);

	ptu_run_f(suite, remove_section, rfix);
	ptu_run_f(suite, remove_bad_vaddr, rfix);
	ptu_run_f(suite, remove_bad_asid, rfix);
	ptu_run_f(suite, remove_by_filename, rfix);
	ptu_run_f(suite, remove_by_filename_bad_asid, rfix);
	ptu_run_f(suite, remove_none_by_filename, rfix);
	ptu_run_f(suite, remove_all_by_filename, ifix);
	ptu_run_f(suite, remove_by_asid, rfix);

	ptu_run_f(suite, copy_empty, ifix);
	ptu_run_f(suite, copy, rfix);
	ptu_run_f(suite, copy_self, rfix);
	ptu_run_f(suite, copy_shrink, rfix);
	ptu_run_f(suite, copy_split, ifix);
	ptu_run_f(suite, copy_merge, ifix);
	ptu_run_f(suite, copy_overlap, ifix);
	ptu_run_f(suite, copy_replace, ifix);

	ptu_run(suite, add_cached_null);
	ptu_run_f(suite, add_cached, ifix);
	ptu_run_f(suite, add_cached_null_asid, ifix);
	ptu_run_f(suite, add_cached_twice, ifix);
	ptu_run_f(suite, add_cached_bad_isid, ifix);

	ptu_run_f(suite, find_null, rfix);
	ptu_run_f(suite, find, rfix);
	ptu_run_f(suite, find_asid, ifix);
	ptu_run_f(suite, find_bad_asid, rfix);
	ptu_run_f(suite, find_nomem, rfix);

	ptu_run_f(suite, validate_null, rfix);
	ptu_run_f(suite, validate, rfix);
	ptu_run_f(suite, validate_bad_asid, rfix);
	ptu_run_f(suite, validate_bad_vaddr, rfix);
	ptu_run_f(suite, validate_bad_offset, rfix);
	ptu_run_f(suite, validate_bad_size, rfix);
	ptu_run_f(suite, validate_bad_isid, rfix);

	return ptunit_report(&suite);
}