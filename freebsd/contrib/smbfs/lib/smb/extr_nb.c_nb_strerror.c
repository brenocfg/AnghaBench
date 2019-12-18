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
 int NBERR_ACTIVE ; 
 int NBERR_HOSTNOTFOUND ; 
 int NBERR_MAX ; 
 char const** nb_err ; 
 char const** nb_err_rcode ; 

const char *
nb_strerror(int error)
{
	if (error == 0)
		return NULL;
	if (error <= NBERR_ACTIVE)
		return nb_err_rcode[error - 1];
	else if (error >= NBERR_HOSTNOTFOUND && error < NBERR_MAX)
		return nb_err[error - NBERR_HOSTNOTFOUND];
	else
		return NULL;
}