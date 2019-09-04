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
struct TYPE_4__ {int type_ip; int /*<<< orphan*/ * host; } ;
typedef  TYPE_1__ GLogItem ;

/* Variables and functions */
 int /*<<< orphan*/  SPEC_SFMT_MIS ; 
 int TYPE_IPINV ; 
 char* extract_braces (char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int invalid_ipaddr (char*,int*) ; 
 char* parsed_string (char*,char**,int /*<<< orphan*/ ) ; 
 int spec_err (TYPE_1__*,int /*<<< orphan*/ ,char,char*) ; 
 int strcspn (char*,char*) ; 
 int /*<<< orphan*/ * xstrdup (char*) ; 

__attribute__((used)) static int
find_xff_host (GLogItem * logitem, char **str, char **p)
{
  char *ptr = NULL, *tkn = NULL, *skips = NULL;
  int invalid_ip = 1, len = 0, type_ip = TYPE_IPINV;

  if (!(skips = extract_braces (p)))
    return spec_err (logitem, SPEC_SFMT_MIS, **p, "{}");

  ptr = *str;
  while (*ptr != '\0') {
    if ((len = strcspn (ptr, skips)) == 0) {
      len++, ptr++;
      goto move;
    }

    ptr += len;
    /* extract possible IP */
    if (!(tkn = parsed_string (ptr, str, 0)))
      break;

    invalid_ip = invalid_ipaddr (tkn, &type_ip);
    /* done, already have IP and current token is not a host */
    if (logitem->host && invalid_ip) {
      free (tkn);
      break;
    }
    if (!logitem->host && !invalid_ip) {
      logitem->host = xstrdup (tkn);
      logitem->type_ip = type_ip;
    }
    free (tkn);

  move:
    *str += len;
  }

  free (skips);

  return logitem->host == NULL;
}