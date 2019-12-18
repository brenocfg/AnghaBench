#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double propself; double propchild; long ncall; long selfcalls; } ;
typedef  TYPE_1__ nltype ;

/* Variables and functions */
 int EQUALTO ; 
 int GREATERTHAN ; 
 int LESSTHAN ; 

int
membercmp(nltype *this, nltype *that)
{
    double	thistime = this -> propself + this -> propchild;
    double	thattime = that -> propself + that -> propchild;
    long	thiscalls = this -> ncall + this -> selfcalls;
    long	thatcalls = that -> ncall + that -> selfcalls;

    if ( thistime > thattime ) {
	return GREATERTHAN;
    }
    if ( thistime < thattime ) {
	return LESSTHAN;
    }
    if ( thiscalls > thatcalls ) {
	return GREATERTHAN;
    }
    if ( thiscalls < thatcalls ) {
	return LESSTHAN;
    }
    return EQUALTO;
}