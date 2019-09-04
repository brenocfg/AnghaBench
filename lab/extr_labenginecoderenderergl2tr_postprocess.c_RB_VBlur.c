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
typedef  int /*<<< orphan*/  FBO_t ;

/* Variables and functions */
 int /*<<< orphan*/  RB_BlurAxis (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 

__attribute__((used)) static void RB_VBlur(FBO_t *srcFbo, FBO_t *dstFbo, float strength)
{
	RB_BlurAxis(srcFbo, dstFbo, strength, qfalse);
}