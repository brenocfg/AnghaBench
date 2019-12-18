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
 int REF_SITE_LEN ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static int
extract_referer_site (const char *referer, char *host)
{
  char *url, *begin, *end;
  int len = 0;

  if ((referer == NULL) || (*referer == '\0'))
    return 1;

  url = strdup (referer);
  if ((begin = strstr (url, "//")) == NULL)
    goto clean;

  begin += 2;
  if ((len = strlen (begin)) == 0)
    goto clean;

  if ((end = strchr (begin, '/')) != NULL)
    len = end - begin;

  if (len == 0)
    goto clean;

  if (len >= REF_SITE_LEN)
    len = REF_SITE_LEN;

  memcpy (host, begin, len);
  host[len] = '\0';
  free (url);
  return 0;
clean:
  free (url);

  return 1;
}