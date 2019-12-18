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
typedef  int /*<<< orphan*/  td_thrhandle_t ;
struct objfile {int flags; char* name; } ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ GET_THREAD (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_THREAD (int /*<<< orphan*/ ) ; 
 int OBJF_SHARED ; 
 int TD_OK ; 
 int /*<<< orphan*/  builtin_type_void_data_ptr ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  extract_typed_address (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_typed_address (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svr4_fetch_objfile_link_map (struct objfile*) ; 
 int td_ta_map_id2thr_p (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int td_thr_tls_get_addr_p (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  thread_agent ; 
 int /*<<< orphan*/  thread_db_err_str (int) ; 

CORE_ADDR
fbsd_thread_get_local_address(ptid_t ptid, struct objfile *objfile,
                              CORE_ADDR offset)
{
  td_thrhandle_t th;
  void *address;
  CORE_ADDR lm;
  void *lm2;
  int ret, is_library = (objfile->flags & OBJF_SHARED);

  if (IS_THREAD (ptid))
    {
      if (!td_thr_tls_get_addr_p)
        error ("Cannot find thread-local interface in thread_db library.");

      /* Get the address of the link map for this objfile. */
      lm = svr4_fetch_objfile_link_map (objfile);

      /* Couldn't find link map. Bail out. */
      if (!lm)
        {
          if (is_library)
            error ("Cannot find shared library `%s' link_map in dynamic"
                   " linker's module list", objfile->name);
          else
            error ("Cannot find executable file `%s' link_map in dynamic"
                   " linker's module list", objfile->name);
        }

      ret = td_ta_map_id2thr_p (thread_agent, GET_THREAD(ptid), &th);

      /* get the address of the variable. */
      store_typed_address(&lm2, builtin_type_void_data_ptr, lm);
      ret = td_thr_tls_get_addr_p (&th, lm2, offset, &address);

      if (ret != TD_OK)
        {
          if (is_library)
            error ("Cannot find thread-local storage for thread %ld, "
                   "shared library %s:\n%s",
                   (long) GET_THREAD (ptid),
                   objfile->name, thread_db_err_str (ret));
          else
            error ("Cannot find thread-local storage for thread %ld, "
                   "executable file %s:\n%s",
                   (long) GET_THREAD (ptid),
                   objfile->name, thread_db_err_str (ret));
        }

      /* Cast assuming host == target. */
      return extract_typed_address(&address, builtin_type_void_data_ptr);
    }
  return (0);
}