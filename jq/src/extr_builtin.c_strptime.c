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
struct tm {int tm_year; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; } ;

/* Variables and functions */
 int sscanf (char const*,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static char *strptime(const char *s, const char *format, struct tm *tm) {
  if (strcmp(format, "%Y-%m-%dT%H:%M:%SZ"))
    return NULL;

  int count, end;
  count = sscanf(s, "%d-%d-%dT%d:%d:%d%n",
                    &tm->tm_year, &tm->tm_mon, &tm->tm_mday,
                    &tm->tm_hour, &tm->tm_min, &tm->tm_sec,
                    &end );
  if (count == 6 && s[end] == 'Z') {
    tm->tm_year -= 1900;
    tm->tm_mon--;
    return (char*)s + end + 1;
  }
  return NULL;
}