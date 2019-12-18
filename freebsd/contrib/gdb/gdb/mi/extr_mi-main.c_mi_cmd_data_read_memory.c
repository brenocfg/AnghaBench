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
struct ui_stream {int /*<<< orphan*/  stream; } ;
struct type {int dummy; } ;
struct mi_opt {char* member_0; int member_1; int member_2; } ;
struct cleanup {int dummy; } ;
typedef  enum opt { ____Placeholder_opt } opt ;
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int MI_CMD_DONE ; 
 int MI_CMD_ERROR ; 
 long atol (char*) ; 
 struct type* builtin_type_int16 ; 
 struct type* builtin_type_int32 ; 
 struct type* builtin_type_int64 ; 
 struct type* builtin_type_int8 ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  fputc_unfiltered (char,int /*<<< orphan*/ ) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 struct cleanup* make_cleanup_ui_out_list_begin_end (int /*<<< orphan*/ ,char*) ; 
 struct cleanup* make_cleanup_ui_out_tuple_begin_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mi_error_message ; 
 int mi_getopt (char*,int,char**,struct mi_opt*,int*,char**) ; 
 int /*<<< orphan*/  null_cleanup ; 
 scalar_t__ parse_and_eval_address (char*) ; 
 int /*<<< orphan*/  print_scalar_formatted (char*,struct type*,char,char,int /*<<< orphan*/ ) ; 
 long target_read_memory_partial (scalar_t__,char*,long,int*) ; 
 int /*<<< orphan*/  ui_file_rewind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_field_core_addr (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ui_out_field_int (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  ui_out_field_stream (int /*<<< orphan*/ ,char*,struct ui_stream*) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ui_out_stream_delete (struct ui_stream*) ; 
 struct ui_stream* ui_out_stream_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  xasprintf (int /*<<< orphan*/ *,char*) ; 
 char* xcalloc (long,int) ; 
 int /*<<< orphan*/  xfree ; 

enum mi_cmd_result
mi_cmd_data_read_memory (char *command, char **argv, int argc)
{
  struct cleanup *cleanups = make_cleanup (null_cleanup, NULL);
  CORE_ADDR addr;
  long total_bytes;
  long nr_cols;
  long nr_rows;
  char word_format;
  struct type *word_type;
  long word_size;
  char word_asize;
  char aschar;
  char *mbuf;
  int nr_bytes;
  long offset = 0;
  int optind = 0;
  char *optarg;
  enum opt
    {
      OFFSET_OPT
    };
  static struct mi_opt opts[] =
  {
    {"o", OFFSET_OPT, 1},
    0
  };

  while (1)
    {
      int opt = mi_getopt ("mi_cmd_data_read_memory", argc, argv, opts,
			   &optind, &optarg);
      if (opt < 0)
	break;
      switch ((enum opt) opt)
	{
	case OFFSET_OPT:
	  offset = atol (optarg);
	  break;
	}
    }
  argv += optind;
  argc -= optind;

  if (argc < 5 || argc > 6)
    {
      xasprintf (&mi_error_message,
		 "mi_cmd_data_read_memory: Usage: ADDR WORD-FORMAT WORD-SIZE NR-ROWS NR-COLS [ASCHAR].");
      return MI_CMD_ERROR;
    }

  /* Extract all the arguments. */

  /* Start address of the memory dump. */
  addr = parse_and_eval_address (argv[0]) + offset;
  /* The format character to use when displaying a memory word. See
     the ``x'' command. */
  word_format = argv[1][0];
  /* The size of the memory word. */
  word_size = atol (argv[2]);
  switch (word_size)
    {
    case 1:
      word_type = builtin_type_int8;
      word_asize = 'b';
      break;
    case 2:
      word_type = builtin_type_int16;
      word_asize = 'h';
      break;
    case 4:
      word_type = builtin_type_int32;
      word_asize = 'w';
      break;
    case 8:
      word_type = builtin_type_int64;
      word_asize = 'g';
      break;
    default:
      word_type = builtin_type_int8;
      word_asize = 'b';
    }
  /* The number of rows */
  nr_rows = atol (argv[3]);
  if (nr_rows <= 0)
    {
      xasprintf (&mi_error_message,
		 "mi_cmd_data_read_memory: invalid number of rows.");
      return MI_CMD_ERROR;
    }
  /* number of bytes per row. */
  nr_cols = atol (argv[4]);
  if (nr_cols <= 0)
    {
      xasprintf (&mi_error_message,
		 "mi_cmd_data_read_memory: invalid number of columns.");
    }
  /* The un-printable character when printing ascii. */
  if (argc == 6)
    aschar = *argv[5];
  else
    aschar = 0;

  /* create a buffer and read it in. */
  total_bytes = word_size * nr_rows * nr_cols;
  mbuf = xcalloc (total_bytes, 1);
  make_cleanup (xfree, mbuf);
  if (mbuf == NULL)
    {
      xasprintf (&mi_error_message,
		 "mi_cmd_data_read_memory: out of memory.");
      return MI_CMD_ERROR;
    }
  nr_bytes = 0;
  while (nr_bytes < total_bytes)
    {
      int error;
      long num = target_read_memory_partial (addr + nr_bytes, mbuf + nr_bytes,
					     total_bytes - nr_bytes,
					     &error);
      if (num <= 0)
	break;
      nr_bytes += num;
    }

  /* output the header information. */
  ui_out_field_core_addr (uiout, "addr", addr);
  ui_out_field_int (uiout, "nr-bytes", nr_bytes);
  ui_out_field_int (uiout, "total-bytes", total_bytes);
  ui_out_field_core_addr (uiout, "next-row", addr + word_size * nr_cols);
  ui_out_field_core_addr (uiout, "prev-row", addr - word_size * nr_cols);
  ui_out_field_core_addr (uiout, "next-page", addr + total_bytes);
  ui_out_field_core_addr (uiout, "prev-page", addr - total_bytes);

  /* Build the result as a two dimentional table. */
  {
    struct ui_stream *stream = ui_out_stream_new (uiout);
    struct cleanup *cleanup_list_memory;
    int row;
    int row_byte;
    cleanup_list_memory = make_cleanup_ui_out_list_begin_end (uiout, "memory");
    for (row = 0, row_byte = 0;
	 row < nr_rows;
	 row++, row_byte += nr_cols * word_size)
      {
	int col;
	int col_byte;
	struct cleanup *cleanup_tuple;
	struct cleanup *cleanup_list_data;
	cleanup_tuple = make_cleanup_ui_out_tuple_begin_end (uiout, NULL);
	ui_out_field_core_addr (uiout, "addr", addr + row_byte);
	/* ui_out_field_core_addr_symbolic (uiout, "saddr", addr + row_byte); */
	cleanup_list_data = make_cleanup_ui_out_list_begin_end (uiout, "data");
	for (col = 0, col_byte = row_byte;
	     col < nr_cols;
	     col++, col_byte += word_size)
	  {
	    if (col_byte + word_size > nr_bytes)
	      {
		ui_out_field_string (uiout, NULL, "N/A");
	      }
	    else
	      {
		ui_file_rewind (stream->stream);
		print_scalar_formatted (mbuf + col_byte, word_type, word_format,
					word_asize, stream->stream);
		ui_out_field_stream (uiout, NULL, stream);
	      }
	  }
	do_cleanups (cleanup_list_data);
	if (aschar)
	  {
	    int byte;
	    ui_file_rewind (stream->stream);
	    for (byte = row_byte; byte < row_byte + word_size * nr_cols; byte++)
	      {
		if (byte >= nr_bytes)
		  {
		    fputc_unfiltered ('X', stream->stream);
		  }
		else if (mbuf[byte] < 32 || mbuf[byte] > 126)
		  {
		    fputc_unfiltered (aschar, stream->stream);
		  }
		else
		  fputc_unfiltered (mbuf[byte], stream->stream);
	      }
	    ui_out_field_stream (uiout, "ascii", stream);
	  }
	do_cleanups (cleanup_tuple);
      }
    ui_out_stream_delete (stream);
    do_cleanups (cleanup_list_memory);
  }
  do_cleanups (cleanups);
  return MI_CMD_DONE;
}