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
typedef  enum lval_type { ____Placeholder_lval_type } lval_type ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 scalar_t__ DEPRECATED_REGISTER_CONVERTIBLE (int) ; 
 scalar_t__ DEPRECATED_REGISTER_CONVERTIBLE_P () ; 
 int /*<<< orphan*/  DEPRECATED_REGISTER_CONVERT_TO_VIRTUAL (int,int /*<<< orphan*/ ,char*,char*) ; 
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int /*<<< orphan*/  DEPRECATED_REGISTER_VIRTUAL_SIZE (int) ; 
 int MAX_REGISTER_SIZE ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 int /*<<< orphan*/  Val_pretty_default ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  deprecated_selected_frame ; 
 int /*<<< orphan*/  frame_register (int /*<<< orphan*/ ,int,int*,int*,int /*<<< orphan*/ *,int*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mi_error_message ; 
 int /*<<< orphan*/  register_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  ui_out_field_stream (int /*<<< orphan*/ ,char*,struct ui_stream*) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ui_out_stream_delete (struct ui_stream*) ; 
 struct ui_stream* ui_out_stream_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  val_print (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xasprintf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
get_register (int regnum, int format)
{
  char raw_buffer[MAX_REGISTER_SIZE];
  char virtual_buffer[MAX_REGISTER_SIZE];
  int optim;
  int realnum;
  CORE_ADDR addr;
  enum lval_type lval;
  static struct ui_stream *stb = NULL;

  stb = ui_out_stream_new (uiout);

  if (format == 'N')
    format = 0;

  frame_register (deprecated_selected_frame, regnum, &optim, &lval, &addr,
		  &realnum, raw_buffer);

  if (optim)
    {
      xasprintf (&mi_error_message, "Optimized out");
      return -1;
    }

  /* Convert raw data to virtual format if necessary.  */

  if (DEPRECATED_REGISTER_CONVERTIBLE_P ()
      && DEPRECATED_REGISTER_CONVERTIBLE (regnum))
    {
      DEPRECATED_REGISTER_CONVERT_TO_VIRTUAL (regnum,
				   register_type (current_gdbarch, regnum),
				   raw_buffer, virtual_buffer);
    }
  else
    memcpy (virtual_buffer, raw_buffer, DEPRECATED_REGISTER_VIRTUAL_SIZE (regnum));

  if (format == 'r')
    {
      int j;
      char *ptr, buf[1024];

      strcpy (buf, "0x");
      ptr = buf + 2;
      for (j = 0; j < DEPRECATED_REGISTER_RAW_SIZE (regnum); j++)
	{
	  int idx = TARGET_BYTE_ORDER == BFD_ENDIAN_BIG ? j
	  : DEPRECATED_REGISTER_RAW_SIZE (regnum) - 1 - j;
	  sprintf (ptr, "%02x", (unsigned char) raw_buffer[idx]);
	  ptr += 2;
	}
      ui_out_field_string (uiout, "value", buf);
      /*fputs_filtered (buf, gdb_stdout); */
    }
  else
    {
      val_print (register_type (current_gdbarch, regnum), virtual_buffer, 0, 0,
		 stb->stream, format, 1, 0, Val_pretty_default);
      ui_out_field_stream (uiout, "value", stb);
      ui_out_stream_delete (stb);
    }
  return 1;
}