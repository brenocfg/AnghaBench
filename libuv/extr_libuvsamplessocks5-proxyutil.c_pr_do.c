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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  fmtbuf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* _getprogname () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char const*,char*) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pr_do(FILE *stream,
                  const char *label,
                  const char *fmt,
                  va_list ap) {
  char fmtbuf[1024];
  vsnprintf(fmtbuf, sizeof(fmtbuf), fmt, ap);
  fprintf(stream, "%s:%s: %s\n", _getprogname(), label, fmtbuf);
}