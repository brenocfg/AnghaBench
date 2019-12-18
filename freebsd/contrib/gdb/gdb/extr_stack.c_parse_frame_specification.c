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
struct value {int dummy; } ;
struct frame_info {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int MAXARGS ; 
 struct frame_info* SETUP_ARBITRARY_FRAME (int,int /*<<< orphan*/ *) ; 
 struct frame_info* create_new_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct frame_info* deprecated_selected_frame ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 struct frame_info* find_relative_frame (struct frame_info*,int*) ; 
 struct frame_info* get_current_frame () ; 
 int /*<<< orphan*/  get_frame_base (struct frame_info*) ; 
 struct frame_info* get_prev_frame (struct frame_info*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  paddr_d (int /*<<< orphan*/ ) ; 
 struct value* parse_and_eval (char*) ; 
 char* savestring (char*,int) ; 
 int /*<<< orphan*/  value_as_address (struct value*) ; 
 int value_as_long (struct value*) ; 
 int /*<<< orphan*/  xfree ; 

struct frame_info *
parse_frame_specification (char *frame_exp)
{
  int numargs = 0;
#define	MAXARGS	4
  CORE_ADDR args[MAXARGS];
  int level;

  if (frame_exp)
    {
      char *addr_string, *p;
      struct cleanup *tmp_cleanup;

      while (*frame_exp == ' ')
	frame_exp++;

      while (*frame_exp)
	{
	  if (numargs > MAXARGS)
	    error ("Too many args in frame specification");
	  /* Parse an argument.  */
	  for (p = frame_exp; *p && *p != ' '; p++)
	    ;
	  addr_string = savestring (frame_exp, p - frame_exp);

	  {
	    struct value *vp;

	    tmp_cleanup = make_cleanup (xfree, addr_string);

	    /* NOTE: we call parse_and_eval and then both
	       value_as_long and value_as_address rather than calling
	       parse_and_eval_long and parse_and_eval_address because
	       of the issue of potential side effects from evaluating
	       the expression.  */
	    vp = parse_and_eval (addr_string);
	    if (numargs == 0)
	      level = value_as_long (vp);

	    args[numargs++] = value_as_address (vp);
	    do_cleanups (tmp_cleanup);
	  }

	  /* Skip spaces, move to possible next arg.  */
	  while (*p == ' ')
	    p++;
	  frame_exp = p;
	}
    }

  switch (numargs)
    {
    case 0:
      if (deprecated_selected_frame == NULL)
	error ("No selected frame.");
      return deprecated_selected_frame;
      /* NOTREACHED */
    case 1:
      {
	struct frame_info *fid =
	find_relative_frame (get_current_frame (), &level);
	struct frame_info *tfid;

	if (level == 0)
	  /* find_relative_frame was successful */
	  return fid;

	/* If SETUP_ARBITRARY_FRAME is defined, then frame specifications
	   take at least 2 addresses.  It is important to detect this case
	   here so that "frame 100" does not give a confusing error message
	   like "frame specification requires two addresses".  This of course
	   does not solve the "frame 100" problem for machines on which
	   a frame specification can be made with one address.  To solve
	   that, we need a new syntax for a specifying a frame by address.
	   I think the cleanest syntax is $frame(0x45) ($frame(0x23,0x45) for
	   two args, etc.), but people might think that is too much typing,
	   so I guess *0x23,0x45 would be a possible alternative (commas
	   really should be used instead of spaces to delimit; using spaces
	   normally works in an expression).  */
#ifdef SETUP_ARBITRARY_FRAME
	error ("No frame %s", paddr_d (args[0]));
#endif

	/* If (s)he specifies the frame with an address, he deserves what
	   (s)he gets.  Still, give the highest one that matches.  */

	for (fid = get_current_frame ();
	     fid && get_frame_base (fid) != args[0];
	     fid = get_prev_frame (fid))
	  ;

	if (fid)
	  while ((tfid = get_prev_frame (fid)) &&
		 (get_frame_base (tfid) == args[0]))
	    fid = tfid;

	/* We couldn't identify the frame as an existing frame, but
	   perhaps we can create one with a single argument.  */
      }

    default:
#ifdef SETUP_ARBITRARY_FRAME
      return SETUP_ARBITRARY_FRAME (numargs, args);
#else
      /* Usual case.  Do it here rather than have everyone supply
         a SETUP_ARBITRARY_FRAME that does this.  */
      if (numargs == 1)
	return create_new_frame (args[0], 0);
      error ("Too many args in frame specification");
#endif
      /* NOTREACHED */
    }
  /* NOTREACHED */
}