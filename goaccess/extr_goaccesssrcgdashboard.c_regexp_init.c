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
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {scalar_t__ icase; } ;

/* Variables and functions */
 int REGEX_ERROR ; 
 int REG_EXTENDED ; 
 int REG_ICASE ; 
 int /*<<< orphan*/  color_error ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ find_t ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  refresh () ; 
 int regcomp (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stdscr ; 

__attribute__((used)) static int
regexp_init (regex_t * regex, const char *pattern)
{
  int y, x, rc;
  char buf[REGEX_ERROR];

  getmaxyx (stdscr, y, x);
  rc = regcomp (regex, pattern, REG_EXTENDED | (find_t.icase ? REG_ICASE : 0));
  /* something went wrong */
  if (rc != 0) {
    regerror (rc, regex, buf, sizeof (buf));
    draw_header (stdscr, buf, "%s", y - 1, 0, x, color_error);
    refresh ();
    return 1;
  }
  return 0;
}