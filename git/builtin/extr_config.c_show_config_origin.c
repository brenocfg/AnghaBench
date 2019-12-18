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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_config_name () ; 
 int /*<<< orphan*/  current_config_origin_type () ; 
 scalar_t__ end_null ; 
 int /*<<< orphan*/  quote_c_style (int /*<<< orphan*/ ,struct strbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char const) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_config_origin(struct strbuf *buf)
{
	const char term = end_null ? '\0' : '\t';

	strbuf_addstr(buf, current_config_origin_type());
	strbuf_addch(buf, ':');
	if (end_null)
		strbuf_addstr(buf, current_config_name());
	else
		quote_c_style(current_config_name(), buf, NULL, 0);
	strbuf_addch(buf, term);
}