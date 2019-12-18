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
struct prompt {int nonewline; int /*<<< orphan*/  Term; scalar_t__ TermMode; scalar_t__ active; } ;

/* Variables and functions */
 int LINE_LEN ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void
prompt_vPrintf(struct prompt *p, const char *fmt, va_list ap)
{
  if (p && p->active) {
    char nfmt[LINE_LEN];
    const char *pfmt;

    if (p->TermMode) {
      /* Stuff '\r' in front of '\n' 'cos we're in raw mode */
      size_t len = strlen(fmt);

      if (len && len < sizeof nfmt - 1 && fmt[len-1] == '\n' &&
          (len == 1 || fmt[len-2] != '\r')) {
        strcpy(nfmt, fmt);
        strcpy(nfmt + len - 1, "\r\n");
        pfmt = nfmt;
      } else
        pfmt = fmt;
    } else
      pfmt = fmt;
    vfprintf(p->Term, pfmt, ap);
    fflush(p->Term);
    p->nonewline = 1;
  }
}