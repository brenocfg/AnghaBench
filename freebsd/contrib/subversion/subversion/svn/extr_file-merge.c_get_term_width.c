#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct winsize {int ws_col; } ;
struct TYPE_4__ {int X; } ;
struct TYPE_5__ {TYPE_1__ dwSize; } ;
typedef  TYPE_2__ CONSOLE_SCREEN_BUFFER_INFO ;

/* Variables and functions */
 scalar_t__ GetConsoleScreenBufferInfo (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  close (int) ; 
 char* getenv (char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct winsize*) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_cstring_atoi (int*,char*) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_term_width(void)
{
  char *columns_env;
#ifdef TIOCGWINSZ
  int fd;

  fd = open("/dev/tty", O_RDONLY, 0);
  if (fd != -1)
    {
      struct winsize ws;
      int error;

      error = ioctl(fd, TIOCGWINSZ, &ws);
      close(fd);
      if (error != -1)
        {
          if (ws.ws_col < 80)
            return 80;
          return ws.ws_col;
        }
    }
#elif defined WIN32
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
      if (csbi.dwSize.X < 80)
        return 80;
      return csbi.dwSize.X;
    }
#endif

  columns_env = getenv("COLUMNS");
  if (columns_env)
    {
      svn_error_t *err;
      int cols;

      err = svn_cstring_atoi(&cols, columns_env);
      if (err)
        {
          svn_error_clear(err);
          return 80;
        }

      if (cols < 80)
        return 80;
      return cols;
    }
  else
    return 80;
}