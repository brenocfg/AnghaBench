#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int c_lflag; int sg_flags; } ;
struct TYPE_5__ {TYPE_1__ d_t; } ;
typedef  TYPE_2__ ttydata_t ;

/* Variables and functions */
 int CBREAK ; 
 int ICANON ; 
 int RAW ; 

int
tty_cooked_mode(ttydata_t *td)
{
#if defined(POSIX) || defined(TERMIO)
    return (td->d_t.c_lflag & ICANON);
#else /* SGTTY */
    return !(td->d_t.sg_flags & (RAW | CBREAK));
#endif /* POSIX || TERMIO */
}