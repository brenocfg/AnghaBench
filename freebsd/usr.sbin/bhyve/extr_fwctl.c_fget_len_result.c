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
struct iovec {int dummy; } ;

/* Variables and functions */
 int fget_result (struct iovec**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fget_len_result(struct iovec **data)
{
	return (fget_result(data, 0));
}