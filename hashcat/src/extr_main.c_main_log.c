#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* event_ctx; } ;
typedef  TYPE_1__ hashcat_ctx_t ;
struct TYPE_7__ {char* msg_buf; size_t msg_len; int msg_newline; size_t prev_len; } ;
typedef  TYPE_2__ event_ctx_t ;
struct TYPE_8__ {int wAttributes; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_3__ CONSOLE_SCREEN_BUFFER_INFO ;

/* Variables and functions */
 char* EOL ; 
 int const FOREGROUND_INTENSITY ; 
 int const FOREGROUND_RED ; 
 int /*<<< orphan*/  GetConsoleScreenBufferInfo (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
#define  LOGLEVEL_ADVICE 131 
#define  LOGLEVEL_ERROR 130 
#define  LOGLEVEL_INFO 129 
#define  LOGLEVEL_WARNING 128 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  SetConsoleTextAttribute (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char const*,size_t const,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_log_clear_line (size_t const,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

__attribute__((used)) static void main_log (hashcat_ctx_t *hashcat_ctx, FILE *fp, const int loglevel)
{
  event_ctx_t *event_ctx = hashcat_ctx->event_ctx;

  const char  *msg_buf     = event_ctx->msg_buf;
  const size_t msg_len     = event_ctx->msg_len;
  const bool   msg_newline = event_ctx->msg_newline;

  // handle last_len

  const size_t prev_len = event_ctx->prev_len;

  if (prev_len) main_log_clear_line (prev_len, fp);

  if (msg_newline == true)
  {
    event_ctx->prev_len = 0;
  }
  else
  {
    event_ctx->prev_len = msg_len;
  }

  // color stuff pre

  #if defined (_WIN)
  HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);

  CONSOLE_SCREEN_BUFFER_INFO con_info;

  GetConsoleScreenBufferInfo (hConsole, &con_info);

  const int orig = con_info.wAttributes;

  switch (loglevel)
  {
    case LOGLEVEL_INFO:
      break;
    case LOGLEVEL_WARNING: SetConsoleTextAttribute (hConsole, 6);
      break;
    case LOGLEVEL_ERROR:   SetConsoleTextAttribute (hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
      break;
    case LOGLEVEL_ADVICE:  SetConsoleTextAttribute (hConsole, 6);
      break;
  }

  #else
  switch (loglevel)
  {
    case LOGLEVEL_INFO:                                   break;
    case LOGLEVEL_WARNING: fwrite ("\033[33m", 5, 1, fp); break;
    case LOGLEVEL_ERROR:   fwrite ("\033[31m", 5, 1, fp); break;
    case LOGLEVEL_ADVICE:  fwrite ("\033[33m", 5, 1, fp); break;
  }
  #endif

  // finally, print

  fwrite (msg_buf, msg_len, 1, fp);

  // color stuff post

  #if defined (_WIN)
  switch (loglevel)
  {
    case LOGLEVEL_INFO:                                              break;
    case LOGLEVEL_WARNING: SetConsoleTextAttribute (hConsole, orig); break;
    case LOGLEVEL_ERROR:   SetConsoleTextAttribute (hConsole, orig); break;
    case LOGLEVEL_ADVICE:  SetConsoleTextAttribute (hConsole, orig); break;
  }
  #else
  switch (loglevel)
  {
    case LOGLEVEL_INFO:                                  break;
    case LOGLEVEL_WARNING: fwrite ("\033[0m", 4, 1, fp); break;
    case LOGLEVEL_ERROR:   fwrite ("\033[0m", 4, 1, fp); break;
    case LOGLEVEL_ADVICE:  fwrite ("\033[0m", 4, 1, fp); break;
  }
  #endif

  // eventual newline

  if (msg_newline == true)
  {
    fwrite (EOL, strlen (EOL), 1, fp);

    // on error, add another newline

    if (loglevel == LOGLEVEL_ERROR)
    {
      fwrite (EOL, strlen (EOL), 1, fp);
    }
  }

  fflush (fp);
}