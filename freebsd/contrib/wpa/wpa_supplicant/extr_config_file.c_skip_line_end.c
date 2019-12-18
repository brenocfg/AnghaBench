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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ newline_terminated (char*,int) ; 

__attribute__((used)) static void skip_line_end(FILE *stream)
{
	char buf[100];
	while (fgets(buf, sizeof(buf), stream)) {
		buf[sizeof(buf) - 1] = '\0';
		if (newline_terminated(buf, sizeof(buf)))
			return;
	}
}