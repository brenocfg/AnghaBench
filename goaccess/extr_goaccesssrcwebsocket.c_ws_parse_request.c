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
typedef  int ptrdiff_t ;

/* Variables and functions */
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strstr (char*,char*) ; 
 char* strtoupper (int /*<<< orphan*/ ) ; 
 char* ws_get_method (char*) ; 
 char* xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static char *
ws_parse_request (char *line, char **method, char **protocol)
{
  const char *meth;
  char *req = NULL, *request = NULL, *proto = NULL;
  ptrdiff_t rlen;

  if ((meth = ws_get_method (line)) == NULL) {
    return NULL;
  } else {
    req = line + strlen (meth);
    if ((proto = strstr (line, " HTTP/1.0")) == NULL &&
        (proto = strstr (line, " HTTP/1.1")) == NULL)
      return NULL;

    req++;
    if ((rlen = proto - req) <= 0)
      return NULL;

    request = xmalloc (rlen + 1);
    strncpy (request, req, rlen);
    request[rlen] = 0;

    (*method) = strtoupper (xstrdup (meth));
    (*protocol) = strtoupper (xstrdup (++proto));
  }

  return request;
}