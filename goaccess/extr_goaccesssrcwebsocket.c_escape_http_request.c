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

/* Variables and functions */
 int strlen (char const*) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static char *
escape_http_request (const char *src)
{
  char *dest, *q;
  const unsigned char *p;

  if (src == NULL || *src == '\0')
    return NULL;

  p = (unsigned char *) src;
  q = dest = xmalloc (strlen (src) * 4 + 1);

  while (*p) {
    switch (*p) {
    case '\\':
      *q++ = '\\';
      *q++ = '\\';
      break;
    case '\n':
      *q++ = '\\';
      *q++ = 'n';
      break;
    case '\r':
      *q++ = '\\';
      *q++ = 'r';
      break;
    case '\t':
      *q++ = '\\';
      *q++ = 't';
      break;
    case '"':
      *q++ = '\\';
      *q++ = '"';
      break;
    default:
      if ((*p < ' ') || (*p >= 0177)) {
        /* not ASCII */
      } else {
        *q++ = *p;
      }
      break;
    }
    p++;
  }
  *q = 0;
  return dest;
}