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
 double _kf_gammap (double,double) ; 
 double _kf_gammaq (double,double) ; 

double kf_gammaq(double s, double z)
{
	return z <= 1. || z < s? 1. - _kf_gammap(s, z) : _kf_gammaq(s, z);
}