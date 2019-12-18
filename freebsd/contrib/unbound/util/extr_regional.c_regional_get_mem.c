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
struct regional {size_t first_size; size_t total_large; } ;

/* Variables and functions */
 int REGIONAL_CHUNK_SIZE ; 
 int count_chunks (struct regional*) ; 

size_t 
regional_get_mem(struct regional* r)
{
	return r->first_size + (count_chunks(r)-1)*REGIONAL_CHUNK_SIZE 
		+ r->total_large;
}