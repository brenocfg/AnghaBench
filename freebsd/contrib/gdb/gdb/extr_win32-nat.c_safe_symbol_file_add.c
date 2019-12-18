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
struct section_addr_info {int dummy; } ;
struct safe_symbol_file_add_args {char* name; int from_tty; int mainline; int flags; struct objfile* ret; struct section_addr_info* addrs; void* out; void* err; } ;
struct objfile {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ERROR ; 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ ,struct safe_symbol_file_add_args*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  gdb_flush (void*) ; 
 void* gdb_stderr ; 
 void* gdb_stdout ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct safe_symbol_file_add_args*) ; 
 int /*<<< orphan*/  safe_symbol_file_add_cleanup ; 
 int /*<<< orphan*/  safe_symbol_file_add_stub ; 
 void* ui_file_new () ; 

__attribute__((used)) static struct objfile *
safe_symbol_file_add (char *name, int from_tty,
		      struct section_addr_info *addrs,
		      int mainline, int flags)
{
  struct safe_symbol_file_add_args p;
  struct cleanup *cleanup;

  cleanup = make_cleanup (safe_symbol_file_add_cleanup, &p);

  p.err = gdb_stderr;
  p.out = gdb_stdout;
  gdb_flush (gdb_stderr);
  gdb_flush (gdb_stdout);
  gdb_stderr = ui_file_new ();
  gdb_stdout = ui_file_new ();
  p.name = name;
  p.from_tty = from_tty;
  p.addrs = addrs;
  p.mainline = mainline;
  p.flags = flags;
  catch_errors (safe_symbol_file_add_stub, &p, "", RETURN_MASK_ERROR);

  do_cleanups (cleanup);
  return p.ret;
}