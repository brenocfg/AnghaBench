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
typedef  int /*<<< orphan*/  floatX ;

/* Variables and functions */
 int /*<<< orphan*/  floatXNaN ; 
 int /*<<< orphan*/  float_flag_invalid ; 
 int /*<<< orphan*/  slow_float_exception_flags ; 

__attribute__((used)) static floatX floatXInvalid( void )
{

    slow_float_exception_flags |= float_flag_invalid;
    return floatXNaN;

}