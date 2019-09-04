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
struct TYPE_2__ {int browsers_hash_idx; int /*<<< orphan*/ ** user_browsers_hash; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BROWSER_TYPE_LEN ; 
 char* alloc_string (char*) ; 
 int /*<<< orphan*/  browsers ; 
 int /*<<< orphan*/ ** browsers_hash ; 
 char* check_http_crawler (char*) ; 
 TYPE_1__ conf ; 
 char* parse_browser (char*,char*,size_t,int /*<<< orphan*/ **) ; 
 char* parse_crawler (char*,char*,char*) ; 
 char* strstr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrncpy (char*,char*,int /*<<< orphan*/ ) ; 

char *
verify_browser (char *str, char *type)
{
  char *match = NULL, *token = NULL;
  int i = 0;
  size_t j = 0;

  if (str == NULL || *str == '\0')
    return NULL;

  /* check user's list */
  for (i = 0; i < conf.browsers_hash_idx; ++i) {
    if ((match = strstr (str, conf.user_browsers_hash[i][0])) == NULL)
      continue;
    return parse_browser (match, type, i, conf.user_browsers_hash);
  }

  if ((match = check_http_crawler (str)) &&
      (token = parse_crawler (str, match, type)))
    return token;

  /* fallback to default browser list */
  for (j = 0; j < ARRAY_SIZE (browsers); ++j) {
    if ((match = strstr (str, browsers_hash[j][0])) == NULL)
      continue;
    return parse_browser (match, type, j, browsers_hash);
  }

  xstrncpy (type, "Unknown", BROWSER_TYPE_LEN);

  return alloc_string ("Unknown");
}