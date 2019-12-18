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
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_buffer_begin (int /*<<< orphan*/  const*) ; 
 size_t ldns_buffer_capacity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_flip (int /*<<< orphan*/ *) ; 
 size_t ldns_buffer_limit (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_buffer_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

void 
ldns_buffer_copy(ldns_buffer* result, const ldns_buffer* from)
{
	size_t tocopy = ldns_buffer_limit(from);

	if(tocopy > ldns_buffer_capacity(result))
		tocopy = ldns_buffer_capacity(result);
	ldns_buffer_clear(result);
	ldns_buffer_write(result, ldns_buffer_begin(from), tocopy);
	ldns_buffer_flip(result);
}