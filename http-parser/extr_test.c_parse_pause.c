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
typedef  int /*<<< orphan*/  http_parser_settings ;

/* Variables and functions */
 int /*<<< orphan*/ * current_pause_parser ; 
 int currently_parsing_eof ; 
 size_t http_parser_execute (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  parser ; 
 int /*<<< orphan*/  settings_pause ; 

size_t parse_pause (const char *buf, size_t len)
{
  size_t nparsed;
  http_parser_settings s = settings_pause;

  currently_parsing_eof = (len == 0);
  current_pause_parser = &s;
  nparsed = http_parser_execute(&parser, current_pause_parser, buf, len);
  return nparsed;
}