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
 int ntpq_getvar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char*,int) ; 
 int /*<<< orphan*/  peervarlen ; 
 int /*<<< orphan*/  peervars ; 

int ntpq_get_peervar( const char *varname, char *varvalue, int maxlen)
{
    return ( ntpq_getvar(peervars,peervarlen,varname,varvalue,maxlen) );
}