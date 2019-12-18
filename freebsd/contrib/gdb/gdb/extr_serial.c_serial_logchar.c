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
struct ui_file {int dummy; } ;

/* Variables and functions */
#define  SERIAL_BREAK 131 
#define  SERIAL_EOF 130 
#define  SERIAL_ERROR 129 
#define  SERIAL_TIMEOUT 128 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf_unfiltered (struct ui_file*,char*,int) ; 
 int /*<<< orphan*/  fputc_unfiltered (char,struct ui_file*) ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  isprint (int) ; 
 scalar_t__ logbase_ascii ; 
 scalar_t__ logbase_hex ; 
 scalar_t__ logbase_octal ; 
 int safe_strerror (int /*<<< orphan*/ ) ; 
 int serial_current_type ; 
 scalar_t__ serial_logbase ; 

__attribute__((used)) static void
serial_logchar (struct ui_file *stream, int ch_type, int ch, int timeout)
{
  if (ch_type != serial_current_type)
    {
      fprintf_unfiltered (stream, "\n%c ", ch_type);
      serial_current_type = ch_type;
    }

  if (serial_logbase != logbase_ascii)
    fputc_unfiltered (' ', stream);

  switch (ch)
    {
    case SERIAL_TIMEOUT:
      fprintf_unfiltered (stream, "<Timeout: %d seconds>", timeout);
      return;
    case SERIAL_ERROR:
      fprintf_unfiltered (stream, "<Error: %s>", safe_strerror (errno));
      return;
    case SERIAL_EOF:
      fputs_unfiltered ("<Eof>", stream);
      return;
    case SERIAL_BREAK:
      fputs_unfiltered ("<Break>", stream);
      return;
    default:
      if (serial_logbase == logbase_hex)
	fprintf_unfiltered (stream, "%02x", ch & 0xff);
      else if (serial_logbase == logbase_octal)
	fprintf_unfiltered (stream, "%03o", ch & 0xff);
      else
	switch (ch)
	  {
	  case '\\':
	    fputs_unfiltered ("\\\\", stream);
	    break;
	  case '\b':
	    fputs_unfiltered ("\\b", stream);
	    break;
	  case '\f':
	    fputs_unfiltered ("\\f", stream);
	    break;
	  case '\n':
	    fputs_unfiltered ("\\n", stream);
	    break;
	  case '\r':
	    fputs_unfiltered ("\\r", stream);
	    break;
	  case '\t':
	    fputs_unfiltered ("\\t", stream);
	    break;
	  case '\v':
	    fputs_unfiltered ("\\v", stream);
	    break;
	  default:
	    fprintf_unfiltered (stream, isprint (ch) ? "%c" : "\\x%02x", ch & 0xFF);
	    break;
	  }
    }
}