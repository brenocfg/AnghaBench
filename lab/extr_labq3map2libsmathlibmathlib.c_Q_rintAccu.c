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
typedef  scalar_t__ vec_accu_t ;

/* Variables and functions */
 int /*<<< orphan*/  floor (scalar_t__) ; 

vec_accu_t Q_rintAccu( vec_accu_t val ){
	return (vec_accu_t) floor( val + 0.5 );
}