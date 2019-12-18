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
struct read_map_ctxt {int /*<<< orphan*/  tail; int /*<<< orphan*/  next; int /*<<< orphan*/  proc; } ;
struct TYPE_2__ {int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
typedef  TYPE_1__ ldr_context_t ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  LDR_NULL_MODULE ; 
 int /*<<< orphan*/  RLD_CONTEXT_ADDRESS ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ ldr_xattach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptid_get_pid (int /*<<< orphan*/ ) ; 
 scalar_t__ target_read_memory (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
open_map (struct read_map_ctxt *ctxt)
{
#ifdef USE_LDR_ROUTINES
  /* Note: As originally written, ldr_my_process() was used to obtain
     the value for ctxt->proc.  This is incorrect, however, since
     ldr_my_process() retrieves the "unique identifier" associated
     with the current process (i.e. GDB) and not the one being
     debugged.  Presumably, the pid of the process being debugged is
     compatible with the "unique identifier" used by the ldr_
     routines, so we use that.  */
  ctxt->proc = ptid_get_pid (inferior_ptid);
  if (ldr_xattach (ctxt->proc) != 0)
    return 0;
  ctxt->next = LDR_NULL_MODULE;
#else
  CORE_ADDR ldr_context_addr, prev, next;
  ldr_context_t ldr_context;

  if (target_read_memory ((CORE_ADDR) RLD_CONTEXT_ADDRESS,
			  (char *) &ldr_context_addr,
			  sizeof (CORE_ADDR)) != 0)
    return 0;
  if (target_read_memory (ldr_context_addr,
			  (char *) &ldr_context,
			  sizeof (ldr_context_t)) != 0)
    return 0;
  ctxt->next = ldr_context.head;
  ctxt->tail = ldr_context.tail;
#endif
  return 1;
}