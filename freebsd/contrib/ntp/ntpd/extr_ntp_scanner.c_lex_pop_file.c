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
 int /*<<< orphan*/  lex_close (struct FILE_INFO*) ; 
 struct FILE_INFO* lex_stack ; 

int/*BOOL*/
lex_pop_file(void)
{
	struct FILE_INFO * head = lex_stack;
	struct FILE_INFO * tail = NULL; 
	
	if (NULL != head) {
		tail = head->st_next;
		if (NULL != tail) {
			lex_stack = tail;
			lex_close(head);
		}
	}
	return (NULL != tail);
}