#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* errstr; } ;
typedef  TYPE_1__ GLogItem ;

/* Variables and functions */
#define  SPEC_SFMT_MIS 131 
#define  SPEC_TOKN_INV 130 
#define  SPEC_TOKN_NUL 129 
#define  SPEC_TOKN_SET 128 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char const*,...) ; 
 char* xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spec_err (GLogItem * logitem, int code, const char spec, const char *tkn)
{
  char *err = NULL;
  const char *fmt = NULL;

  switch (code) {
  case SPEC_TOKN_INV:
    fmt = "Token '%s' doesn't match specifier '%%%c'";
    err = xmalloc (snprintf (NULL, 0, fmt, (tkn ? tkn : "-"), spec) + 1);
    sprintf (err, fmt, (tkn ? tkn : "-"), spec);
    break;
  case SPEC_TOKN_SET:
    fmt = "Token already set for '%%%c' specifier.";
    err = xmalloc (snprintf (NULL, 0, fmt, spec) + 1);
    sprintf (err, fmt, spec);
    break;
  case SPEC_TOKN_NUL:
    fmt = "Token for '%%%c' specifier is NULL.";
    err = xmalloc (snprintf (NULL, 0, fmt, spec) + 1);
    sprintf (err, fmt, spec);
    break;
  case SPEC_SFMT_MIS:
    fmt = "Missing braces '%s' and ignore chars for specifier '%%%c'";
    err = xmalloc (snprintf (NULL, 0, fmt, (tkn ? tkn : "-"), spec) + 1);
    sprintf (err, fmt, (tkn ? tkn : "-"), spec);
    break;
  }
  logitem->errstr = err;

  return 1;
}