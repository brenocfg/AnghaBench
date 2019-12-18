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
struct FILE_INFO {struct FILE_INFO* st_next; } ;

/* Variables and functions */
 struct FILE_INFO* lex_open (char const*,char const*) ; 
 struct FILE_INFO* lex_stack ; 

int/*BOOL*/ lex_push_file(
	const char * path,
	const char * mode
	)
{
	struct FILE_INFO * next = NULL;

	if (NULL != path) {
		next = lex_open(path, mode);
		if (NULL != next) {
			next->st_next = lex_stack;
			lex_stack = next;
		}
	}
	return (NULL != next);
}