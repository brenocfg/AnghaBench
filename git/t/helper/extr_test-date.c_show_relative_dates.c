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
typedef  int /*<<< orphan*/  time_t ;
struct strbuf {char* buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  atoi (char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 int /*<<< orphan*/  show_date_relative (int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void show_relative_dates(const char **argv)
{
	struct strbuf buf = STRBUF_INIT;

	for (; *argv; argv++) {
		time_t t = atoi(*argv);
		show_date_relative(t, &buf);
		printf("%s -> %s\n", *argv, buf.buf);
	}
	strbuf_release(&buf);
}