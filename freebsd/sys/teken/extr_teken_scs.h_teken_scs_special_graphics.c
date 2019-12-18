#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int t_stateflags; } ;
typedef  TYPE_1__ teken_t ;
typedef  char teken_char_t ;

/* Variables and functions */
 int TS_8BIT ; 
 char* teken_boxdrawing_8bit ; 
 char* teken_boxdrawing_unicode ; 

__attribute__((used)) static teken_char_t
teken_scs_special_graphics(const teken_t *t, teken_char_t c)
{

	/* Box drawing. */
	if (c >= '`' && c <= '~')
		return (t->t_stateflags & TS_8BIT ?
		    teken_boxdrawing_8bit[c - '`'] :
		    teken_boxdrawing_unicode[c - '`']);
	return (c);
}