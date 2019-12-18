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
typedef  enum http_method { ____Placeholder_http_method } http_method ;

/* Variables and functions */
 char const* ELEM_AT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  method_strings ; 

const char *
http_method_str (enum http_method m)
{
  return ELEM_AT(method_strings, m, "<unknown>");
}