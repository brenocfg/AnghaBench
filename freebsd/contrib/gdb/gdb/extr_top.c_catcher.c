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
struct ui_out {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  int return_mask ;
typedef  enum return_reason { ____Placeholder_return_reason } return_reason ;
typedef  int (* catch_exceptions_ftype ) (struct ui_out*,void*) ;
typedef  int /*<<< orphan*/  SIGJMP_BUF ;

/* Variables and functions */
 int RETURN_MASK (int) ; 
 int RETURN_MASK_ERROR ; 
 int RETURN_MASK_QUIT ; 
 int SIGSETJMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * catch_return ; 
 char* error_last_message () ; 
 char* error_pre_print ; 
 char* quit_pre_print ; 
 int /*<<< orphan*/  restore_cleanups (struct cleanup*) ; 
 struct cleanup* save_cleanups () ; 
 int stub1 (struct ui_out*,void*) ; 
 int /*<<< orphan*/  throw_exception (int) ; 
 struct ui_out* uiout ; 

__attribute__((used)) static void
catcher (catch_exceptions_ftype *func,
	 struct ui_out *func_uiout,
	 void *func_args,
	 int *func_val,
	 enum return_reason *func_caught,
	 char *errstring,
	 char **gdberrmsg,
	 return_mask mask)
{
  SIGJMP_BUF *saved_catch;
  SIGJMP_BUF catch;
  struct cleanup *saved_cleanup_chain;
  char *saved_error_pre_print;
  char *saved_quit_pre_print;
  struct ui_out *saved_uiout;

  /* Return value from SIGSETJMP(): enum return_reason if error or
     quit caught, 0 otherwise. */
  int caught;

  /* Return value from FUNC(): Hopefully non-zero. Explicitly set to
     zero if an error quit was caught.  */
  int val;

  /* Override error/quit messages during FUNC. */

  saved_error_pre_print = error_pre_print;
  saved_quit_pre_print = quit_pre_print;

  if (mask & RETURN_MASK_ERROR)
    error_pre_print = errstring;
  if (mask & RETURN_MASK_QUIT)
    quit_pre_print = errstring;

  /* Override the global ``struct ui_out'' builder.  */

  saved_uiout = uiout;
  uiout = func_uiout;

  /* Prevent error/quit during FUNC from calling cleanups established
     prior to here. */

  saved_cleanup_chain = save_cleanups ();

  /* Call FUNC, catching error/quit events. */

  saved_catch = catch_return;
  catch_return = &catch;
  caught = SIGSETJMP (catch);
  if (!caught)
    val = (*func) (func_uiout, func_args);
  else
    {
      val = 0;
      /* If caller wants a copy of the low-level error message, make one.  
         This is used in the case of a silent error whereby the caller
         may optionally want to issue the message.  */
      if (gdberrmsg)
	*gdberrmsg = error_last_message ();
    }
  catch_return = saved_catch;

  /* FIXME: cagney/1999-11-05: A correct FUNC implementation will
     clean things up (restoring the cleanup chain) to the state they
     were just prior to the call.  Unfortunately, many FUNC's are not
     that well behaved.  This could be fixed by adding either a
     do_cleanups call (to cover the problem) or an assertion check to
     detect bad FUNCs code. */

  /* Restore the cleanup chain, the error/quit messages, and the uiout
     builder, to their original states. */

  restore_cleanups (saved_cleanup_chain);

  uiout = saved_uiout;

  if (mask & RETURN_MASK_QUIT)
    quit_pre_print = saved_quit_pre_print;
  if (mask & RETURN_MASK_ERROR)
    error_pre_print = saved_error_pre_print;

  /* Return normally if no error/quit event occurred or this catcher
     can handle this exception.  The caller analyses the func return
     values.  */

  if (!caught || (mask & RETURN_MASK (caught)))
    {
      *func_val = val;
      *func_caught = caught;
      return;
    }

  /* The caller didn't request that the event be caught, relay the
     event to the next containing catch_errors(). */

  throw_exception (caught);
}