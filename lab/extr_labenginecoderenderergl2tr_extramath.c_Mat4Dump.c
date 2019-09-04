#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * mat4_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ALL ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Mat4Dump( const mat4_t in )
{
	ri.Printf(PRINT_ALL, "%3.5f %3.5f %3.5f %3.5f\n", in[ 0], in[ 4], in[ 8], in[12]);
	ri.Printf(PRINT_ALL, "%3.5f %3.5f %3.5f %3.5f\n", in[ 1], in[ 5], in[ 9], in[13]);
	ri.Printf(PRINT_ALL, "%3.5f %3.5f %3.5f %3.5f\n", in[ 2], in[ 6], in[10], in[14]);
	ri.Printf(PRINT_ALL, "%3.5f %3.5f %3.5f %3.5f\n", in[ 3], in[ 7], in[11], in[15]);
}