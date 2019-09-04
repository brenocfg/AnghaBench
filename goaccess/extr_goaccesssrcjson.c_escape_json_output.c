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
typedef  int /*<<< orphan*/  GJSON ;

/* Variables and functions */
 int /*<<< orphan*/  escape_json_other (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  pjson (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
escape_json_output (GJSON * json, char *s)
{
  while (*s) {
    switch (*s) {
      /* These are required JSON special characters that need to be escaped. */
    case '"':
      pjson (json, "\\\"");
      break;
    case '\\':
      pjson (json, "\\\\");
      break;
    case '\b':
      pjson (json, "\\b");
      break;
    case '\f':
      pjson (json, "\\f");
      break;
    case '\n':
      pjson (json, "\\n");
      break;
    case '\r':
      pjson (json, "\\r");
      break;
    case '\t':
      pjson (json, "\\t");
      break;
    case '/':
      pjson (json, "\\/");
      break;
    default:
      escape_json_other (json, &s);
      break;
    }
    s++;
  }
}