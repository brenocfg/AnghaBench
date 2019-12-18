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
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  krb5_storage ;

/* Variables and functions */
 int /*<<< orphan*/  FD (int /*<<< orphan*/ *) ; 
 int errno ; 
 int ftruncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fd_trunc(krb5_storage * sp, off_t offset)
{
    if (ftruncate(FD(sp), offset) == -1)
	return errno;
    return 0;
}