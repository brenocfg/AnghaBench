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
union key {int /*<<< orphan*/  name; } ;
struct passwd {int dummy; } ;

/* Variables and functions */
 int getpwnam_r (int /*<<< orphan*/ ,struct passwd*,char*,size_t,struct passwd**) ; 

__attribute__((used)) static int
wrap_getpwnam_r(union key key, struct passwd *pwd, char *buffer,
    size_t bufsize, struct passwd **res)
{
	return (getpwnam_r(key.name, pwd, buffer, bufsize, res));
}