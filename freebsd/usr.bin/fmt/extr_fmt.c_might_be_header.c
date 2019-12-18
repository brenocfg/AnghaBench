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
typedef  char wchar_t ;

/* Variables and functions */
 scalar_t__ iswalnum (char const) ; 
 scalar_t__ iswspace (char const) ; 
 int /*<<< orphan*/  iswupper (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
might_be_header(const wchar_t *line)
{
	if (!iswupper(*line++))
		return 0;
	while (*line && (iswalnum(*line) || *line == '-'))
		++line;
	return (*line == ':' && iswspace(line[1]));
}