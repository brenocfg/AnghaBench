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
struct option_header {size_t option_length; } ;
struct block_cursor {int dummy; } ;

/* Variables and functions */
 void* get_from_block_data (struct block_cursor*,size_t,char*) ; 

__attribute__((used)) static void *
get_optvalue_from_block_data(struct block_cursor *cursor,
    struct option_header *opthdr, char *errbuf)
{
	size_t padded_option_len;
	void *optvalue;

	/* Pad option length to 4-byte boundary */
	padded_option_len = opthdr->option_length;
	padded_option_len = ((padded_option_len + 3)/4)*4;

	optvalue = get_from_block_data(cursor, padded_option_len, errbuf);
	if (optvalue == NULL) {
		/*
		 * Option value is cut short.
		 */
		return (NULL);
	}

	return (optvalue);
}