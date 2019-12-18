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
struct section_fixture {int /*<<< orphan*/  fini; int /*<<< orphan*/  init; } ;
struct ptunit_suite {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  attach_bad_iscache ; 
 int /*<<< orphan*/  attach_bad_map ; 
 int /*<<< orphan*/  attach_bad_ucount ; 
 int /*<<< orphan*/  attach_detach ; 
 int /*<<< orphan*/  attach_map ; 
 int /*<<< orphan*/  attach_map_overflow ; 
 int /*<<< orphan*/  attach_null ; 
 int /*<<< orphan*/  attach_overflow ; 
 int /*<<< orphan*/  bcache_alloc_free ; 
 int /*<<< orphan*/  bcache_alloc_nomap ; 
 int /*<<< orphan*/  bcache_alloc_twice ; 
 int /*<<< orphan*/  cache_null ; 
 int /*<<< orphan*/  create ; 
 int /*<<< orphan*/  create_bad_offset ; 
 int /*<<< orphan*/  create_empty ; 
 int /*<<< orphan*/  create_truncated ; 
 int /*<<< orphan*/  detach_bad_iscache ; 
 int /*<<< orphan*/  detach_null ; 
 int /*<<< orphan*/  filename_null ; 
 int /*<<< orphan*/  get_null ; 
 int /*<<< orphan*/  get_overflow ; 
 int /*<<< orphan*/  get_put ; 
 int /*<<< orphan*/  init_no_bcache ; 
 int /*<<< orphan*/  map_change ; 
 int /*<<< orphan*/  map_null ; 
 int /*<<< orphan*/  map_overflow ; 
 int /*<<< orphan*/  map_put ; 
 int /*<<< orphan*/  map_unmap ; 
 int /*<<< orphan*/  memsize_map_bcache ; 
 int /*<<< orphan*/  memsize_map_nobcache ; 
 int /*<<< orphan*/  memsize_nomap ; 
 int /*<<< orphan*/  memsize_null ; 
 int /*<<< orphan*/  memsize_unmap ; 
 int /*<<< orphan*/  offset_null ; 
 int /*<<< orphan*/  ptu_run (struct ptunit_suite,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_run_f (struct ptunit_suite,int /*<<< orphan*/ ,struct section_fixture) ; 
 int /*<<< orphan*/  ptu_run_fp (struct ptunit_suite,int /*<<< orphan*/ ,struct section_fixture,int /*<<< orphan*/ ) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 
 int /*<<< orphan*/  put_null ; 
 int /*<<< orphan*/  read ; 
 int /*<<< orphan*/  read_from_truncated ; 
 int /*<<< orphan*/  read_nomap ; 
 int /*<<< orphan*/  read_nomem ; 
 int /*<<< orphan*/  read_null ; 
 int /*<<< orphan*/  read_offset ; 
 int /*<<< orphan*/  read_overflow ; 
 int /*<<< orphan*/  read_overflow_32bit ; 
 int /*<<< orphan*/  read_truncated ; 
 int /*<<< orphan*/  read_unmap_map ; 
 int /*<<< orphan*/  sfix_fini ; 
 int /*<<< orphan*/  sfix_init ; 
 int /*<<< orphan*/  size_null ; 
 int /*<<< orphan*/  stress ; 
 int /*<<< orphan*/  unmap_nomap ; 
 int /*<<< orphan*/  unmap_null ; 
 int /*<<< orphan*/  worker_bcache ; 
 int /*<<< orphan*/  worker_read ; 

int main(int argc, char **argv)
{
	struct section_fixture sfix;
	struct ptunit_suite suite;

	sfix.init = sfix_init;
	sfix.fini = sfix_fini;

	suite = ptunit_mk_suite(argc, argv);

	ptu_run_f(suite, create, sfix);
	ptu_run_f(suite, create_bad_offset, sfix);
	ptu_run_f(suite, create_truncated, sfix);
	ptu_run_f(suite, create_empty, sfix);

	ptu_run(suite, filename_null);
	ptu_run(suite, offset_null);
	ptu_run(suite, size_null);
	ptu_run(suite, get_null);
	ptu_run(suite, put_null);
	ptu_run(suite, attach_null);
	ptu_run(suite, detach_null);
	ptu_run(suite, map_null);
	ptu_run(suite, unmap_null);
	ptu_run(suite, cache_null);

	ptu_run_f(suite, get_overflow, sfix);
	ptu_run_f(suite, attach_overflow, sfix);
	ptu_run_f(suite, attach_bad_ucount, sfix);
	ptu_run_f(suite, map_change, sfix);
	ptu_run_f(suite, map_put, sfix);
	ptu_run_f(suite, unmap_nomap, sfix);
	ptu_run_f(suite, map_overflow, sfix);
	ptu_run_f(suite, get_put, sfix);
	ptu_run_f(suite, attach_detach, sfix);
	ptu_run_f(suite, attach_bad_iscache, sfix);
	ptu_run_f(suite, detach_bad_iscache, sfix);
	ptu_run_f(suite, map_unmap, sfix);
	ptu_run_f(suite, attach_map, sfix);
	ptu_run_f(suite, attach_bad_map, sfix);
	ptu_run_f(suite, attach_map_overflow, sfix);
	ptu_run_f(suite, read, sfix);
	ptu_run_f(suite, read_null, sfix);
	ptu_run_f(suite, read_offset, sfix);
	ptu_run_f(suite, read_truncated, sfix);
	ptu_run_f(suite, read_from_truncated, sfix);
	ptu_run_f(suite, read_nomem, sfix);
	ptu_run_f(suite, read_overflow, sfix);
	ptu_run_f(suite, read_overflow_32bit, sfix);
	ptu_run_f(suite, read_nomap, sfix);
	ptu_run_f(suite, read_unmap_map, sfix);

	ptu_run_f(suite, init_no_bcache, sfix);
	ptu_run_f(suite, bcache_alloc_free, sfix);
	ptu_run_f(suite, bcache_alloc_twice, sfix);
	ptu_run_f(suite, bcache_alloc_nomap, sfix);

	ptu_run_f(suite, memsize_null, sfix);
	ptu_run_f(suite, memsize_nomap, sfix);
	ptu_run_f(suite, memsize_unmap, sfix);
	ptu_run_f(suite, memsize_map_nobcache, sfix);
	ptu_run_f(suite, memsize_map_bcache, sfix);

	ptu_run_fp(suite, stress, sfix, worker_bcache);
	ptu_run_fp(suite, stress, sfix, worker_read);

	return ptunit_report(&suite);
}