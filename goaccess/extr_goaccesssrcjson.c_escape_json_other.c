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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  GJSON ;

/* Variables and functions */
 scalar_t__ escape_html_output ; 
 int /*<<< orphan*/  pjson (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char) ; 

__attribute__((used)) static void
escape_json_other (GJSON * json, char **s)
{
  /* Since JSON data is bootstrapped into the HTML document of a report,
   * then we perform the following four translations in case weird stuff
   * is put into the document.
   *
   * Note: The following scenario assumes that the user manually makes
   * the HTML report a PHP file (GoAccess doesn't allow the creation of a
   * PHP file):
   *
   * /index.html<?php eval(base_decode('iZWNobyAiPGgxPkhFTExPPC9oMT4iOw=='));?>
   */
  if (escape_html_output) {
    switch (**s) {
    case '\'':
      pjson (json, "&#39;");
      return;
    case '&':
      pjson (json, "&amp;");
      return;
    case '<':
      pjson (json, "&lt;");
      return;
    case '>':
      pjson (json, "&gt;");
      return;
    }
  }

  if ((uint8_t) ** s <= 0x1f) {
    /* Control characters (U+0000 through U+001F) */
    char buf[8];
    snprintf (buf, sizeof buf, "\\u%04x", **s);
    pjson (json, "%s", buf);
  } else if ((uint8_t) ** s == 0xe2 && (uint8_t) * (*s + 1) == 0x80 &&
             (uint8_t) * (*s + 2) == 0xa8) {
    /* Line separator (U+2028) - 0xE2 0x80 0xA8 */
    pjson (json, "\\u2028");
    *s += 2;
  } else if ((uint8_t) ** s == 0xe2 && (uint8_t) * (*s + 1) == 0x80 &&
             (uint8_t) * (*s + 2) == 0xa9) {
    /* Paragraph separator (U+2019) - 0xE2 0x80 0xA9 */
    pjson (json, "\\u2029");
    *s += 2;
  } else {
    char buf[2];
    snprintf (buf, sizeof buf, "%c", **s);
    pjson (json, "%s", buf);
  }
}