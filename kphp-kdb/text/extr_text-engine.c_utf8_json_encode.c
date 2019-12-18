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
 int* cp1251_unicode_codes ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* utf8_char (char*,int) ; 
 scalar_t__ utf8_mode ; 

int utf8_json_encode (char *to, int to_size, char *from, int from_size) {
  char *to_end = to + to_size - 8;
  char *from_end = from + from_size;
  char *wptr = to;
  int c, uc;

  if ((unsigned) from_size > 0xffffff || to_size <= 8) {
    fprintf (stderr, "utf8_json_encode: invalid initial data\n");
    return -1;
  }

  if (utf8_mode) {
    while (from < from_end) {
      if (wptr > to_end) {
	fprintf (stderr, "utf8_json_encode: buffer overflow\n");
	return -1;
      }
      c = *from++;
      switch (c) {
      case '"': case '\\': case '/':
	*wptr++ = '\\';
	break;
      case '\n':
	*wptr++ = '\\';
	c = 'n';
	break;
      case '\r':
	*wptr++ = '\\';
	c = 'r';
	break;
      case '\t':
	*wptr++ = '\\';
	c = 't';
	break;
      case '\b':
	*wptr++ = '\\';
	c = 'b';
	break;
      case '\f':
	*wptr++ = '\\';
	c = 'f';
	break;
      }
      if (!(c & -32)) {
	wptr += sprintf (wptr, "\\u%04x", c);
      } else {
	*wptr++ = c;
      }
    }
    return wptr - to;
  }

  while (from < from_end) {
    if (wptr > to_end) {
      fprintf (stderr, "utf8_json_encode: buffer overflow\n");
      return -1;
    }
    c = *from++;
    if (c < 0) {
      uc = cp1251_unicode_codes[c+128];
      wptr = utf8_char (wptr, uc);
      continue;
    }
    if (c == '&') {
      char *ptr = from;
      if (from == from_end) {
        return wptr - to;
      }
      if (ptr[0] == '#') {
        ptr++;
        uc = 0;
        while (ptr < from_end && ptr < from + 8 && *ptr >= '0' && *ptr <= '9') {
          uc = uc * 10 + (*ptr++ - '0');
        }
        if (ptr == from_end) {
          return wptr - to;
        }
        if (*ptr == ';' && uc > 0 && uc != '<' && uc != '>') {
          from = ptr + 1;
          c = uc;
        }
      } else if (ptr[0] >= 'a' && ptr[0] <= 'z') {
        while (ptr < from_end && ptr < from + 16 && *ptr >= 'a' && *ptr <= 'z') {
          ptr++;
        }
        if (ptr == from_end) {
          return wptr - to;
        }
      }
    }
    switch (c) {
    case '"': case '\\': case '/':
      *wptr++ = '\\';
      break;
    case '\n':
      *wptr++ = '\\';
      c = 'n';
      break;
    case '\r':
      *wptr++ = '\\';
      c = 'r';
      break;
    case '\t':
      *wptr++ = '\\';
      c = 't';
      break;
    case '\b':
      *wptr++ = '\\';
      c = 'b';
      break;
    case '\f':
      *wptr++ = '\\';
      c = 'f';
      break;
    }
    if (!(c & -32)) {
      wptr += sprintf (wptr, "\\u%04x", c);
    } else {
      wptr = utf8_char (wptr, c);
    }
  }

  return wptr - to;
}