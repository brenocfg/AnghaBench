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
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 void db_capture_write (char*,int) ; 

void
db_capture_writech(char ch)
{

	return (db_capture_write(&ch, sizeof(ch)));
}