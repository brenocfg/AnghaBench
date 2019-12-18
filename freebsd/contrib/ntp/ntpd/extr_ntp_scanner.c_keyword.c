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
 size_t COUNTOF (char**) ; 
 int LOWEST_KEYWORD_ID ; 
 char** keyword_text ; 

const char *
keyword(
	int token
	)
{
	size_t i;
	const char *text;

	i = token - LOWEST_KEYWORD_ID;

	if (i < COUNTOF(keyword_text))
		text = keyword_text[i];
	else
		text = NULL;

	return (text != NULL)
		   ? text
		   : "(keyword not found)";
}