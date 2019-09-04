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
struct mdfour {int dummy; } ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  mdfour_begin (struct mdfour*) ; 
 int /*<<< orphan*/  mdfour_result (struct mdfour*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdfour_update (struct mdfour*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mdfour(byte *out, byte *in, int n)
{
	struct mdfour md;
	mdfour_begin(&md);
	mdfour_update(&md, in, n);
	mdfour_result(&md, out);
}