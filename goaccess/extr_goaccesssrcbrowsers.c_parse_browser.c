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
 int /*<<< orphan*/  BROWSER_TYPE_LEN ; 
 char* alloc_string (char*) ; 
 char* char_replace (char*,char,char) ; 
 size_t count_matches (char*,char) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 char* parse_opera (char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 
 char* strpbrk (char*,char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  xstrncpy (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
parse_browser (char *match, char *type, int i, char ***hash)
{
  char *b = NULL, *ptr = NULL, *slh = NULL;
  size_t cnt = 0, space = 0;

  /* Check if there are spaces in the token string, that way strpbrk
   * does not stop at the first space within the token string */
  if ((cnt = count_matches (hash[i][0], ' ')) && (b = match)) {
    while (space++ < cnt && (b = strchr (b, ' ')))
      b++;
  } else
    b = match;

  xstrncpy (type, hash[i][1], BROWSER_TYPE_LEN);
  /* Internet Explorer 11 */
  if (strstr (match, "rv:11") && strstr (match, "Trident/7.0")) {
    return alloc_string ("MSIE/11.0");
  }
  /* Opera +15 uses OPR/# */
  if (strstr (match, "OPR") != NULL && (slh = strrchr (match, '/'))) {
    return parse_opera (slh);
  }
  /* Opera has the version number at the end */
  if (strstr (match, "Opera") && (slh = strrchr (match, '/')) && match < slh) {
    memmove (match + 5, slh, strlen (slh) + 1);
  }
  /* IE Old */
  if (strstr (match, "MSIE") != NULL) {
    if ((ptr = strpbrk (match, ";)-")) != NULL)
      *ptr = '\0';
    match = char_replace (match, ' ', '/');
  }
  /* all others */
  else if ((ptr = strpbrk (b, ";) ")) != NULL) {
    *ptr = '\0';
  }

  return alloc_string (match);
}