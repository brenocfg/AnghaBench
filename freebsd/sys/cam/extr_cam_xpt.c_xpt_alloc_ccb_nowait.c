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
typedef  union ccb {int dummy; } ccb ;

/* Variables and functions */
 int /*<<< orphan*/  M_CAMCCB ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 union ccb* malloc (int,int /*<<< orphan*/ ,int) ; 

union ccb *
xpt_alloc_ccb_nowait()
{
	union ccb *new_ccb;

	new_ccb = malloc(sizeof(*new_ccb), M_CAMCCB, M_ZERO|M_NOWAIT);
	return (new_ccb);
}