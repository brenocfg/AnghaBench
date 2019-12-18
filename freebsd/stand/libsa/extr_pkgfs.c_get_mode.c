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
struct TYPE_2__ {int /*<<< orphan*/  ut_mode; } ;
struct tarfile {TYPE_1__ tf_hdr; } ;

/* Variables and functions */
 int pkg_atol (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
get_mode(struct tarfile *tf)
{
	return (pkg_atol(tf->tf_hdr.ut_mode, sizeof(tf->tf_hdr.ut_mode)));
}