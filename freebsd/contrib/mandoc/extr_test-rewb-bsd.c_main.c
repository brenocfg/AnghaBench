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
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int REG_EXTENDED ; 
 scalar_t__ REG_NOMATCH ; 
 int REG_NOSUB ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
main(void)
{
	regex_t	 re;

	if (regcomp(&re, "[[:<:]]word[[:>:]]", REG_EXTENDED | REG_NOSUB))
		return 1;
	if (regexec(&re, "the word is here", 0, NULL, 0))
		return 2;
	if (regexec(&re, "same word", 0, NULL, 0))
		return 3;
	if (regexec(&re, "word again", 0, NULL, 0))
		return 4;
	if (regexec(&re, "word", 0, NULL, 0))
		return 5;
	if (regexec(&re, "wordy", 0, NULL, 0) != REG_NOMATCH)
		return 6;
	if (regexec(&re, "sword", 0, NULL, 0) != REG_NOMATCH)
		return 7;
	if (regexec(&re, "reworded", 0, NULL, 0) != REG_NOMATCH)
		return 8;
	return 0;
}