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
struct TYPE_2__ {scalar_t__ real_os; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPESYS_TYPE_LEN ; 
 char* alloc_string (int /*<<< orphan*/ ) ; 
 TYPE_1__ conf ; 
 int count_matches (char const*,char) ; 
 char* get_real_android (char*) ; 
 char* get_real_mac_osx (char*) ; 
 char* get_real_win (char*) ; 
 char const*** os ; 
 char* parse_android (char*) ; 
 char const* parse_ios (char*,int) ; 
 char* parse_osx (char*) ; 
 int /*<<< orphan*/  parse_others (char*,int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 
 char* xstrdup (char const*) ; 
 int /*<<< orphan*/  xstrncpy (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
parse_os (const char *str, char *tkn, char *os_type, int idx)
{
  char *b;
  int spaces = 0;

  xstrncpy (os_type, os[idx][1], OPESYS_TYPE_LEN);
  /* Windows */
  if ((strstr (str, "Windows")) != NULL)
    return conf.real_os && (b = get_real_win (tkn)) ? b : xstrdup (os[idx][0]);
  /* Android */
  if ((strstr (tkn, "Android")) != NULL) {
    tkn = parse_android (tkn);
    return conf.real_os ? get_real_android (tkn) : xstrdup (tkn);
  }
  /* iOS */
  if (strstr (tkn, "iPad") || strstr (tkn, "iPod"))
    return xstrdup (parse_ios (tkn, 4));
  if (strstr (tkn, "iPhone"))
    return xstrdup (parse_ios (tkn, 6));
  /* Mac OS X */
  if ((strstr (tkn, "OS X")) != NULL) {
    tkn = parse_osx (tkn);
    return conf.real_os ? get_real_mac_osx (tkn) : xstrdup (tkn);
  }
  /* Darwin - capture the first part of agents such as:
   * Slack/248000 CFNetwork/808.0.2 Darwin/16.0.0 */
  if ((strstr (tkn, "Darwin")) != NULL) {
    if ((b = strchr (str, ' ')))
      *b = 0;
    return xstrdup (str);
  }
  /* all others */
  spaces = count_matches (os[idx][0], ' ');

  return alloc_string (parse_others (tkn, spaces));
}