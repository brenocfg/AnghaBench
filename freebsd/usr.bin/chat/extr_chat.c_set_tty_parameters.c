#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int c_iflag; int* c_cc; scalar_t__ c_lflag; scalar_t__ c_oflag; } ;
typedef  TYPE_1__ term_parms ;

/* Variables and functions */
 int IGNBRK ; 
 int IGNPAR ; 
 int ISTRIP ; 
 size_t VERASE ; 
 size_t VKILL ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int /*<<< orphan*/  fatal (int,char*) ; 
 scalar_t__ get_term_param (TYPE_1__*) ; 
 int have_tty_parameters ; 
 TYPE_1__ saved_tty_parameters ; 
 scalar_t__ set_term_param (TYPE_1__*) ; 

void set_tty_parameters(void)
{
#if defined(get_term_param)
    term_parms t;

    if (get_term_param (&t) < 0)
	fatal(2, "Can't get terminal parameters: %m");

    saved_tty_parameters = t;
    have_tty_parameters  = 1;

    t.c_iflag     |= IGNBRK | ISTRIP | IGNPAR;
    t.c_oflag      = 0;
    t.c_lflag      = 0;
    t.c_cc[VERASE] =
    t.c_cc[VKILL]  = 0;
    t.c_cc[VMIN]   = 1;
    t.c_cc[VTIME]  = 0;

    if (set_term_param (&t) < 0)
	fatal(2, "Can't set terminal parameters: %m");
#endif
}