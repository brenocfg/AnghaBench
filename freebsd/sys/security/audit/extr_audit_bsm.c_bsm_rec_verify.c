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
 char AUT_HEADER32 ; 
 char AUT_HEADER32_EX ; 
 char AUT_HEADER64 ; 
 char AUT_HEADER64_EX ; 

int
bsm_rec_verify(void *rec)
{
	char c = *(char *)rec;

	/*
	 * Check the token ID of the first token; it has to be a header
	 * token.
	 *
	 * XXXAUDIT There needs to be a token structure to map a token.
	 * XXXAUDIT 'Shouldn't be simply looking at the first char.
	 */
	if ((c != AUT_HEADER32) && (c != AUT_HEADER32_EX) &&
	    (c != AUT_HEADER64) && (c != AUT_HEADER64_EX))
		return (0);
	return (1);
}