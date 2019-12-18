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
struct symtab {int dummy; } ;
struct mi_opt {char* member_0; int member_1; int member_2; } ;
typedef  enum opt { ____Placeholder_opt } opt ;
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int MI_CMD_DONE ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  find_line_pc (struct symtab*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ find_pc_partial_function (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_disassembly (int /*<<< orphan*/ ,char*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct symtab* lookup_symtab (char*) ; 
 int mi_getopt (char*,int,char**,struct mi_opt*,int*,char**) ; 
 int /*<<< orphan*/  parse_and_eval_address (char*) ; 
 int /*<<< orphan*/  uiout ; 
 char* xstrdup (char*) ; 

enum mi_cmd_result
mi_cmd_disassemble (char *command, char **argv, int argc)
{
  enum mi_cmd_result retval;
  CORE_ADDR start;

  int mixed_source_and_assembly;
  struct symtab *s;

  /* Which options have we processed ... */
  int file_seen = 0;
  int line_seen = 0;
  int num_seen = 0;
  int start_seen = 0;
  int end_seen = 0;

  /* ... and their corresponding value. */
  char *file_string = NULL;
  int line_num = -1;
  int how_many = -1;
  CORE_ADDR low = 0;
  CORE_ADDR high = 0;

  /* Options processing stuff. */
  int optind = 0;
  char *optarg;
  enum opt
  {
    FILE_OPT, LINE_OPT, NUM_OPT, START_OPT, END_OPT
  };
  static struct mi_opt opts[] = {
    {"f", FILE_OPT, 1},
    {"l", LINE_OPT, 1},
    {"n", NUM_OPT, 1},
    {"s", START_OPT, 1},
    {"e", END_OPT, 1},
    0
  };

  /* Get the options with their arguments. Keep track of what we
     encountered. */
  while (1)
    {
      int opt = mi_getopt ("mi_cmd_disassemble", argc, argv, opts,
			   &optind, &optarg);
      if (opt < 0)
	break;
      switch ((enum opt) opt)
	{
	case FILE_OPT:
	  file_string = xstrdup (optarg);
	  file_seen = 1;
	  break;
	case LINE_OPT:
	  line_num = atoi (optarg);
	  line_seen = 1;
	  break;
	case NUM_OPT:
	  how_many = atoi (optarg);
	  num_seen = 1;
	  break;
	case START_OPT:
	  low = parse_and_eval_address (optarg);
	  start_seen = 1;
	  break;
	case END_OPT:
	  high = parse_and_eval_address (optarg);
	  end_seen = 1;
	  break;
	}
    }
  argv += optind;
  argc -= optind;

  /* Allow only filename + linenum (with how_many which is not
     required) OR start_addr + and_addr */

  if (!((line_seen && file_seen && num_seen && !start_seen && !end_seen)
	|| (line_seen && file_seen && !num_seen && !start_seen && !end_seen)
	|| (!line_seen && !file_seen && !num_seen && start_seen && end_seen)))
    error
      ("mi_cmd_disassemble: Usage: ( [-f filename -l linenum [-n howmany]] | [-s startaddr -e endaddr]) [--] mixed_mode.");

  if (argc != 1)
    error
      ("mi_cmd_disassemble: Usage: [-f filename -l linenum [-n howmany]] [-s startaddr -e endaddr] [--] mixed_mode.");

  mixed_source_and_assembly = atoi (argv[0]);
  if ((mixed_source_and_assembly != 0) && (mixed_source_and_assembly != 1))
    error ("mi_cmd_disassemble: Mixed_mode argument must be 0 or 1.");


  /* We must get the function beginning and end where line_num is
     contained. */

  if (line_seen && file_seen)
    {
      s = lookup_symtab (file_string);
      if (s == NULL)
	error ("mi_cmd_disassemble: Invalid filename.");
      if (!find_line_pc (s, line_num, &start))
	error ("mi_cmd_disassemble: Invalid line number");
      if (find_pc_partial_function (start, NULL, &low, &high) == 0)
	error ("mi_cmd_disassemble: No function contains specified address");
    }

  gdb_disassembly (uiout,
  		   file_string,
		   line_num,
		   mixed_source_and_assembly, how_many, low, high);

  return MI_CMD_DONE;
}