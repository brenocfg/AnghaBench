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
 unsigned int TRACE_ALL ; 
 unsigned int TRACE_ARGS ; 
 unsigned int TRACE_CONT ; 
 unsigned int TRACE_EXPANSION ; 
 unsigned int TRACE_FILENAME ; 
 unsigned int TRACE_ID ; 
 unsigned int TRACE_INPUT ; 
 unsigned int TRACE_LINENO ; 
 unsigned int TRACE_NEWFILE ; 
 unsigned int TRACE_QUOTE ; 

__attribute__((used)) static unsigned int
letter_to_flag(int c)
{
	switch(c) {
	case 'a':
		return TRACE_ARGS;
	case 'e':
		return TRACE_EXPANSION;
	case 'q':
		return TRACE_QUOTE;
	case 'c':
		return TRACE_CONT;
	case 'x':
		return TRACE_ID;
	case 'f':
		return TRACE_FILENAME;
	case 'l':
		return TRACE_LINENO;
	case 'p':
		return TRACE_NEWFILE;
	case 'i':
		return TRACE_INPUT;
	case 't':
		return TRACE_ALL;
	case 'V':
		return ~0;
	default:
		return 0;
	}
}