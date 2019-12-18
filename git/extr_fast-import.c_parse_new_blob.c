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
 int /*<<< orphan*/  last_blob ; 
 int /*<<< orphan*/  next_mark ; 
 int /*<<< orphan*/  parse_and_store_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_mark () ; 
 int /*<<< orphan*/  parse_original_identifier () ; 
 int /*<<< orphan*/  read_next_command () ; 

__attribute__((used)) static void parse_new_blob(void)
{
	read_next_command();
	parse_mark();
	parse_original_identifier();
	parse_and_store_blob(&last_blob, NULL, next_mark);
}