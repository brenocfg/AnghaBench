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
struct iscache_fixture {void* fini; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  add ; 
 int /*<<< orphan*/  add_different_same_laddr ; 
 int /*<<< orphan*/  add_file ; 
 int /*<<< orphan*/  add_file_different_same_laddr ; 
 int /*<<< orphan*/  add_file_null ; 
 int /*<<< orphan*/  add_file_same ; 
 int /*<<< orphan*/  add_file_same_different_laddr ; 
 int /*<<< orphan*/  add_no_name ; 
 int /*<<< orphan*/  add_null ; 
 int /*<<< orphan*/  add_same ; 
 int /*<<< orphan*/  add_same_different_laddr ; 
 int /*<<< orphan*/  add_twice ; 
 int /*<<< orphan*/  add_twice_different_laddr ; 
 void* cfix_fini ; 
 int /*<<< orphan*/  cfix_init ; 
 int /*<<< orphan*/  clear_empty ; 
 int /*<<< orphan*/  clear_find ; 
 int /*<<< orphan*/  clear_lookup ; 
 int /*<<< orphan*/  clear_null ; 
 int /*<<< orphan*/  dfix_init ; 
 int /*<<< orphan*/  find ; 
 int /*<<< orphan*/  find_bad_filename ; 
 int /*<<< orphan*/  find_bad_laddr ; 
 int /*<<< orphan*/  find_bad_offset ; 
 int /*<<< orphan*/  find_bad_size ; 
 int /*<<< orphan*/  find_empty ; 
 int /*<<< orphan*/  find_null ; 
 int /*<<< orphan*/  find_null_filename ; 
 int /*<<< orphan*/  fini_null ; 
 int /*<<< orphan*/  free_null ; 
 int /*<<< orphan*/  init_fini ; 
 int /*<<< orphan*/  init_null ; 
 int /*<<< orphan*/  lookup ; 
 int /*<<< orphan*/  lookup_bad_isid ; 
 int /*<<< orphan*/  lookup_null ; 
 int /*<<< orphan*/  lru_bcache_clear ; 
 int /*<<< orphan*/  lru_bcache_evict ; 
 int /*<<< orphan*/  lru_clear ; 
 int /*<<< orphan*/  lru_limit_evict ; 
 int /*<<< orphan*/  lru_map ; 
 int /*<<< orphan*/  lru_map_add_front ; 
 int /*<<< orphan*/  lru_map_evict ; 
 int /*<<< orphan*/  lru_map_move_front ; 
 int /*<<< orphan*/  lru_map_nodup ; 
 int /*<<< orphan*/  lru_map_too_big ; 
 int /*<<< orphan*/  lru_read ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  name_none ; 
 int /*<<< orphan*/  name_null ; 
 int /*<<< orphan*/  ptu_run (struct ptunit_suite,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_run_f (struct ptunit_suite,int /*<<< orphan*/ ,struct iscache_fixture) ; 
 int /*<<< orphan*/  ptu_run_fp (struct ptunit_suite,int /*<<< orphan*/ ,struct iscache_fixture,int /*<<< orphan*/ ) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 
 int /*<<< orphan*/  read ; 
 int /*<<< orphan*/  read_bad_isid ; 
 int /*<<< orphan*/  read_bad_vaddr ; 
 int /*<<< orphan*/  read_null ; 
 int /*<<< orphan*/  read_truncate ; 
 int /*<<< orphan*/  sfix_init ; 
 int /*<<< orphan*/  stress ; 
 int /*<<< orphan*/  worker_add ; 
 int /*<<< orphan*/  worker_add_clear ; 
 int /*<<< orphan*/  worker_add_file ; 
 int /*<<< orphan*/  worker_add_file_clear ; 
 int /*<<< orphan*/  worker_add_file_map ; 
 int /*<<< orphan*/  worker_add_map ; 
 int /*<<< orphan*/  worker_map ; 
 int /*<<< orphan*/  worker_map_bcache ; 
 int /*<<< orphan*/  worker_map_limit ; 

int main(int argc, char **argv)
{
	struct iscache_fixture cfix, dfix, sfix;
	struct ptunit_suite suite;

	cfix.init = cfix_init;
	cfix.fini = cfix_fini;

	dfix.init = dfix_init;
	dfix.fini = cfix_fini;

	sfix.init = sfix_init;
	sfix.fini = cfix_fini;

	suite = ptunit_mk_suite(argc, argv);

	ptu_run(suite, init_null);
	ptu_run(suite, fini_null);
	ptu_run(suite, name_null);
	ptu_run(suite, add_null);
	ptu_run(suite, find_null);
	ptu_run(suite, lookup_null);
	ptu_run(suite, clear_null);
	ptu_run(suite, free_null);
	ptu_run(suite, add_file_null);
	ptu_run(suite, read_null);

	ptu_run_f(suite, name, dfix);
	ptu_run_f(suite, name_none, dfix);

	ptu_run_f(suite, init_fini, cfix);
	ptu_run_f(suite, add, cfix);
	ptu_run_f(suite, add_no_name, cfix);
	ptu_run_f(suite, add_file, cfix);

	ptu_run_f(suite, find, cfix);
	ptu_run_f(suite, find_empty, cfix);
	ptu_run_f(suite, find_bad_filename, cfix);
	ptu_run_f(suite, find_null_filename, cfix);
	ptu_run_f(suite, find_bad_offset, cfix);
	ptu_run_f(suite, find_bad_size, cfix);
	ptu_run_f(suite, find_bad_laddr, cfix);

	ptu_run_f(suite, lookup, cfix);
	ptu_run_f(suite, lookup_bad_isid, cfix);

	ptu_run_f(suite, clear_empty, cfix);
	ptu_run_f(suite, clear_find, cfix);
	ptu_run_f(suite, clear_lookup, cfix);

	ptu_run_f(suite, add_twice, cfix);
	ptu_run_f(suite, add_same, cfix);
	ptu_run_f(suite, add_twice_different_laddr, cfix);
	ptu_run_f(suite, add_same_different_laddr, cfix);
	ptu_run_f(suite, add_different_same_laddr, cfix);

	ptu_run_f(suite, add_file_same, cfix);
	ptu_run_f(suite, add_file_same_different_laddr, cfix);
	ptu_run_f(suite, add_file_different_same_laddr, cfix);

	ptu_run_f(suite, read, cfix);
	ptu_run_f(suite, read_truncate, cfix);
	ptu_run_f(suite, read_bad_vaddr, cfix);
	ptu_run_f(suite, read_bad_isid, cfix);

	ptu_run_f(suite, lru_map, cfix);
	ptu_run_f(suite, lru_read, cfix);
	ptu_run_f(suite, lru_map_nodup, cfix);
	ptu_run_f(suite, lru_map_too_big, cfix);
	ptu_run_f(suite, lru_map_add_front, cfix);
	ptu_run_f(suite, lru_map_move_front, cfix);
	ptu_run_f(suite, lru_map_evict, cfix);
	ptu_run_f(suite, lru_limit_evict, cfix);
	ptu_run_f(suite, lru_bcache_evict, cfix);
	ptu_run_f(suite, lru_bcache_clear, cfix);
	ptu_run_f(suite, lru_clear, cfix);

	ptu_run_fp(suite, stress, cfix, worker_add);
	ptu_run_fp(suite, stress, cfix, worker_add_file);
	ptu_run_fp(suite, stress, sfix, worker_map);
	ptu_run_fp(suite, stress, sfix, worker_map_limit);
	ptu_run_fp(suite, stress, sfix, worker_map_bcache);
	ptu_run_fp(suite, stress, cfix, worker_add_map);
	ptu_run_fp(suite, stress, cfix, worker_add_clear);
	ptu_run_fp(suite, stress, cfix, worker_add_file_map);
	ptu_run_fp(suite, stress, cfix, worker_add_file_clear);

	return ptunit_report(&suite);
}