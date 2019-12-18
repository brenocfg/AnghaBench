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

/* Variables and functions */
 int currently_parsing_eof ; 
 size_t http_parser_execute (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  parser ; 
 int /*<<< orphan*/  settings_connect ; 

size_t parse_connect (const char *buf, size_t len)
{
  size_t nparsed;
  currently_parsing_eof = (len == 0);
  nparsed = http_parser_execute(&parser, &settings_connect, buf, len);
  return nparsed;
}