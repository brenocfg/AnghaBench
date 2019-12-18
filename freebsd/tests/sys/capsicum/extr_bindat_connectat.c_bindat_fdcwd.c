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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int bindat (int /*<<< orphan*/ ,int,struct sockaddr const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bindat_fdcwd(int s, const struct sockaddr *name, socklen_t namelen)
{

	return (bindat(AT_FDCWD, s, name, namelen));
}