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
typedef  int apr_size_t ;

/* Variables and functions */
 char* svn_eol__find_eol_start (char*,int) ; 

const char *
svn_eol__detect_eol(char *buf, apr_size_t len, char **eolp)
{
  char *eol;

  eol = svn_eol__find_eol_start(buf, len);
  if (eol)
    {
      if (eolp)
        *eolp = eol;

      if (*eol == '\n')
        return "\n";

      /* We found a CR. */
      ++eol;
      if (eol == buf + len || *eol != '\n')
        return "\r";
      return "\r\n";
    }

  return NULL;
}