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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ data_prot ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ sec_complete ; 
 scalar_t__ sec_read (int /*<<< orphan*/ ,char*,int) ; 

int
sec_getc(FILE *F)
{
    if(sec_complete && data_prot) {
	char c;
	if(sec_read(fileno(F), &c, 1) <= 0)
	    return EOF;
	return c;
    } else
	return getc(F);
}