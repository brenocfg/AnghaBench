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
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  enum verbosity_value { ____Placeholder_verbosity_value } verbosity_value ;

/* Variables and functions */
 int /*<<< orphan*/  log_hex_f (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 int verbosity ; 

void log_buf(enum verbosity_value level, const char* msg, sldns_buffer* buf)
{
	if(verbosity < level)
		return;
	log_hex_f(level, msg, sldns_buffer_begin(buf), sldns_buffer_limit(buf));
}