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
struct sleepqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SC_LOOKUP (void*) ; 
 struct sleepqueue* lookup (int /*<<< orphan*/ ,void*) ; 

struct sleepqueue *
_sleepq_lookup(void *wchan)
{
	return (lookup(SC_LOOKUP(wchan), wchan));
}