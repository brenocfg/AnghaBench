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
 long double qS1 ; 
 long double qS2 ; 
 long double qS3 ; 
 long double qS4 ; 
 long double qS5 ; 
 long double qS6 ; 
 long double qS7 ; 
 long double qS8 ; 
 long double qS9 ; 

__attribute__((used)) static inline long double
Q(long double x)
{

	return (1.0 + x * (qS1 + x * (qS2 + x * (qS3 + x * (qS4 + x * \
		(qS5 + x * (qS6 + x * (qS7 + x * (qS8 + x * qS9)))))))));
}