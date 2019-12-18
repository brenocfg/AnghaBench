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
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ntp_opterr ; 
 char const* prog ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
badopt(
	const char *mess,
	int ch
	)
{
	if (ntp_opterr) {
		fputs(prog, stderr);
		fputs(mess, stderr);
		(void) putc(ch, stderr);
		(void) putc('\n', stderr);
	}
	return ('?');
}