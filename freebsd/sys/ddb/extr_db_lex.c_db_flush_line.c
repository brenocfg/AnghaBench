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
 void* db_endlp ; 
 void* db_line ; 
 void* db_lp ; 

__attribute__((used)) static void
db_flush_line()
{
	db_lp = db_line;
	db_endlp = db_line;
}