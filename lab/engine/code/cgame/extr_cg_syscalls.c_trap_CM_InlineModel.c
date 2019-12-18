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
typedef  int /*<<< orphan*/  clipHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CG_CM_INLINEMODEL ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int) ; 

clipHandle_t trap_CM_InlineModel( int index ) {
	return syscall( CG_CM_INLINEMODEL, index );
}