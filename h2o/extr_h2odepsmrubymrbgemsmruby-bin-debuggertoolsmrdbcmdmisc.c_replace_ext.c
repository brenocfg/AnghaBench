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
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 char* strrchr (char const*,char) ; 

char*
replace_ext(mrb_state *mrb, const char *filename, const char *ext)
{
  size_t len;
  const char *p;
  char *s;

  if (filename == NULL) {
    return NULL;
  }

  if ((p = strrchr(filename, '.')) != NULL && strchr(p, '/') == NULL) {
    len = p - filename;
  }
  else {
    len = strlen(filename);
  }

  s = (char*)mrb_malloc(mrb, len + strlen(ext) + 1);
  memset(s, '\0', len + strlen(ext) + 1);
  strncpy(s, filename, len);
  strcat(s, ext);

  return s;
}