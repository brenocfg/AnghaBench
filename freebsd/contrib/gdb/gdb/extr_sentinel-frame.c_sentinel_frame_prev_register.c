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
struct frame_unwind_cache {int /*<<< orphan*/  regcache; } ;
struct frame_info {int dummy; } ;
typedef  enum lval_type { ____Placeholder_lval_type } lval_type ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 int lval_register ; 
 int /*<<< orphan*/  regcache_cooked_read (int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  register_offset_hack (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sentinel_frame_prev_register (struct frame_info *next_frame,
			      void **this_prologue_cache,
			      int regnum, int *optimized,
			      enum lval_type *lvalp, CORE_ADDR *addrp,
			      int *realnum, void *bufferp)
{
  struct frame_unwind_cache *cache = *this_prologue_cache;
  /* Describe the register's location.  A reg-frame maps all registers
     onto the corresponding hardware register.  */
  *optimized = 0;
  *lvalp = lval_register;
  *addrp = register_offset_hack (current_gdbarch, regnum);
  *realnum = regnum;

  /* If needed, find and return the value of the register.  */
  if (bufferp != NULL)
    {
      /* Return the actual value.  */
      /* Use the regcache_cooked_read() method so that it, on the fly,
         constructs either a raw or pseudo register from the raw
         register cache.  */
      regcache_cooked_read (cache->regcache, regnum, bufferp);
    }
}