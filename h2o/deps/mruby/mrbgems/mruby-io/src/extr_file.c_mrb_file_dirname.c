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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int _MAX_DIR ; 
 int _MAX_DRIVE ; 
 int /*<<< orphan*/  _splitpath (char const*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_locale_free (char*) ; 
 char* mrb_locale_from_utf8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_str_to_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static mrb_value
mrb_file_dirname(mrb_state *mrb, mrb_value klass)
{
#if defined(_WIN32) || defined(_WIN64)
  char dname[_MAX_DIR], vname[_MAX_DRIVE];
  char buffer[_MAX_DRIVE + _MAX_DIR];
  char *path;
  size_t ridx;
  mrb_value s;
  mrb_get_args(mrb, "S", &s);
  path = mrb_locale_from_utf8(mrb_str_to_cstr(mrb, s), -1);
  _splitpath((const char*)path, vname, dname, NULL, NULL);
  snprintf(buffer, _MAX_DRIVE + _MAX_DIR, "%s%s", vname, dname);
  mrb_locale_free(path);
  ridx = strlen(buffer);
  if (ridx == 0) {
    strncpy(buffer, ".", 2);  /* null terminated */
  } else if (ridx > 1) {
    ridx--;
    while (ridx > 0 && (buffer[ridx] == '/' || buffer[ridx] == '\\')) {
      buffer[ridx] = '\0';  /* remove last char */
      ridx--;
    }
  }
  return mrb_str_new_cstr(mrb, buffer);
#else
  char *dname, *path;
  mrb_value s;
  mrb_get_args(mrb, "S", &s);
  path = mrb_locale_from_utf8(mrb_str_to_cstr(mrb, s), -1);

  if ((dname = dirname(path)) == NULL) {
    mrb_locale_free(path);
    mrb_sys_fail(mrb, "dirname");
  }
  mrb_locale_free(path);
  return mrb_str_new_cstr(mrb, dname);
#endif
}