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
 struct FILE_INFO* lex_stack ; 

size_t
lex_level(void)
{
	size_t            cnt = 0;
	struct FILE_INFO *ipf = lex_stack;

	while (NULL != ipf) {
		cnt++;
		ipf = ipf->st_next;
	}
	return cnt;
}