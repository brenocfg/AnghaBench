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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Update (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
MD5Update_int(void *ctx, void *buf, u_int len)
{

	MD5Update(ctx, buf, len);
	return (0);
}