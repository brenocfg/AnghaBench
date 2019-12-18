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
typedef  int ptrdiff_t ;
struct TYPE_2__ {scalar_t__ append_protocol; scalar_t__ append_method; } ;

/* Variables and functions */
 char* alloc_string (char*) ; 
 TYPE_1__ conf ; 
 char* decode_url (char*) ; 
 char* extract_method (char*) ; 
 char* extract_protocol (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 char* strtoupper (char*) ; 
 char* xmalloc (int) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static char *
parse_req (char *line, char **method, char **protocol)
{
  char *req = NULL, *request = NULL, *dreq = NULL, *ptr = NULL;
  const char *meth, *proto;
  ptrdiff_t rlen;

  meth = extract_method (line);

  /* couldn't find a method, so use the whole request line */
  if (meth == NULL) {
    request = xstrdup (line);
  }
  /* method found, attempt to parse request */
  else {
    req = line + strlen (meth);
    if (!(ptr = strrchr (req, ' ')) || !(proto = extract_protocol (++ptr)))
      return alloc_string ("-");

    req++;
    if ((rlen = ptr - req) <= 0)
      return alloc_string ("-");

    request = xmalloc (rlen + 1);
    strncpy (request, req, rlen);
    request[rlen] = 0;

    if (conf.append_method)
      (*method) = strtoupper (xstrdup (meth));

    if (conf.append_protocol)
      (*protocol) = strtoupper (xstrdup (proto));
  }

  if (!(dreq = decode_url (request)))
    return request;
  else if (*dreq == '\0') {
    free (dreq);
    return request;
  }

  free (request);
  return dreq;
}