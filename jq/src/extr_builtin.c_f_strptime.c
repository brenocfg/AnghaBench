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
typedef  int /*<<< orphan*/  tm ;
struct tm {int tm_wday; int tm_yday; scalar_t__ tm_mday; int tm_mon; } ;
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  jq_state ;

/* Variables and functions */
 scalar_t__ JV_KIND_STRING ; 
 int /*<<< orphan*/  isspace (char const) ; 
 int /*<<< orphan*/  jv_array_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char const*) ; 
 int /*<<< orphan*/  jv_string_fmt (char*,char const*,char const*) ; 
 char* jv_string_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ret_error2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tm_wday (struct tm*) ; 
 int /*<<< orphan*/  set_tm_yday (struct tm*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strptime (char const*,char const*,struct tm*) ; 
 int /*<<< orphan*/  tm2jv (struct tm*) ; 

__attribute__((used)) static jv f_strptime(jq_state *jq, jv a, jv b) {
  if (jv_get_kind(a) != JV_KIND_STRING || jv_get_kind(b) != JV_KIND_STRING) {
    return ret_error2(a, b, jv_string("strptime/1 requires string inputs and arguments"));
  }

  struct tm tm;
  memset(&tm, 0, sizeof(tm));
  tm.tm_wday = 8; // sentinel
  tm.tm_yday = 367; // sentinel
  const char *input = jv_string_value(a);
  const char *fmt = jv_string_value(b);

#ifndef HAVE_STRPTIME
  if (strcmp(fmt, "%Y-%m-%dT%H:%M:%SZ")) {
    return ret_error2(a, b, jv_string("strptime/1 only supports ISO 8601 on this platform"));
  }
#endif
  const char *end = strptime(input, fmt, &tm);
  if (end == NULL || (*end != '\0' && !isspace(*end))) {
    return ret_error2(a, b, jv_string_fmt("date \"%s\" does not match format \"%s\"", input, fmt));
  }
  jv_free(b);
  /*
   * This is OS X or some *BSD whose strptime() is just not that
   * helpful!
   *
   * We don't know that the format string did involve parsing a
   * year, or a month (if tm->tm_mon == 0).  But with our invalid
   * day-of-week and day-of-year sentinel checks above, the worst
   * this can do is produce garbage.
   */
#ifdef __APPLE__
  /*
   * Apple has made it worse, and different versions of the OS have different
   * behaviors. Some versions just don't touch the fields, but others do, and
   * sometimes provide wrong answers, at that! We can't tell at compile-time
   * which behavior the target system will have, so instead we always use our
   * functions to set these on OS X, and document that %u and %j are
   * unsupported on OS X.
   */
  set_tm_wday(&tm);
  set_tm_yday(&tm);
#else
  if (tm.tm_wday == 8 && tm.tm_mday != 0 && tm.tm_mon >= 0 && tm.tm_mon <= 11)
    set_tm_wday(&tm);
  if (tm.tm_yday == 367 && tm.tm_mday != 0 && tm.tm_mon >= 0 && tm.tm_mon <= 11)
    set_tm_yday(&tm);
#endif
  jv r = tm2jv(&tm);
  if (*end != '\0')
    r = jv_array_append(r, jv_string(end));
  jv_free(a); // must come after `*end` because `end` is a pointer into `a`'s string
  return r;
}