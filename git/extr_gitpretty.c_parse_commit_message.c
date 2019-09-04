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
struct format_commit_context {char* message; int message_off; int subject_off; int body_off; int commit_message_parsed; } ;

/* Variables and functions */
 char* format_subject (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 char* skip_blank_lines (char const*) ; 

__attribute__((used)) static void parse_commit_message(struct format_commit_context *c)
{
	const char *msg = c->message + c->message_off;
	const char *start = c->message;

	msg = skip_blank_lines(msg);
	c->subject_off = msg - start;

	msg = format_subject(NULL, msg, NULL);
	msg = skip_blank_lines(msg);
	c->body_off = msg - start;

	c->commit_message_parsed = 1;
}