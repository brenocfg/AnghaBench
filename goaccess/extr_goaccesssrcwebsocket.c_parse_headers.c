#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* buf; } ;
typedef  TYPE_1__ WSHeaders ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char*) ; 
 int ws_set_header_fields (char*,TYPE_1__*) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static int
parse_headers (WSHeaders * headers)
{
  char *tmp = NULL;
  const char *buffer = headers->buf;
  const char *line = buffer, *next = NULL;
  int len = 0;

  while (line) {
    if ((next = strstr (line, "\r\n")) != NULL)
      len = (next - line);
    else
      len = strlen (line);

    if (len <= 0)
      return 1;

    tmp = xmalloc (len + 1);
    memcpy (tmp, line, len);
    tmp[len] = '\0';

    if (ws_set_header_fields (tmp, headers) == 1) {
      free (tmp);
      return 1;
    }

    free (tmp);
    line = next ? (next + 2) : NULL;

    if (strcmp (next, "\r\n\r\n") == 0)
      break;
  }

  return 0;
}