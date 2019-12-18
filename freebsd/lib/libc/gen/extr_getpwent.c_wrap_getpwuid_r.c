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
union key {int /*<<< orphan*/  uid; } ;
struct passwd {int dummy; } ;

/* Variables and functions */
 int getpwuid_r (int /*<<< orphan*/ ,struct passwd*,char*,size_t,struct passwd**) ; 

__attribute__((used)) static int
wrap_getpwuid_r(union key key, struct passwd *pwd, char *buffer,
    size_t bufsize, struct passwd **res)
{
	return (getpwuid_r(key.uid, pwd, buffer, bufsize, res));
}