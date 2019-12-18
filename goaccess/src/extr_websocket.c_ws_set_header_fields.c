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
struct TYPE_4__ {char* path; char* method; char* protocol; } ;
typedef  TYPE_1__ WSHeaders ;

/* Variables and functions */
 scalar_t__ isspace (unsigned char) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/ * strpbrk (char*,char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 char* ws_parse_request (char*,char**,char**) ; 
 int /*<<< orphan*/  ws_set_header_key_value (TYPE_1__*,char*,char*) ; 

__attribute__((used)) static int
ws_set_header_fields (char *line, WSHeaders * headers)
{
  char *path = NULL, *method = NULL, *proto = NULL, *p, *value;

  if (line[0] == '\n' || line[0] == '\r')
    return 1;

  if ((strstr (line, "GET ")) || (strstr (line, "get "))) {
    if ((path = ws_parse_request (line, &method, &proto)) == NULL)
      return 1;
    headers->path = path;
    headers->method = method;
    headers->protocol = proto;

    return 0;
  }

  if ((p = strchr (line, ':')) == NULL)
    return 1;

  value = p + 1;
  while (p != line && isspace ((unsigned char) *(p - 1)))
    p--;

  if (p == line)
    return 1;

  *p = '\0';
  if (strpbrk (line, " \t") != NULL) {
    *p = ' ';
    return 1;
  }
  while (isspace ((unsigned char) *value))
    value++;

  ws_set_header_key_value (headers, line, value);

  return 0;
}