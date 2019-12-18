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
struct servent {int dummy; } ;
struct key {int /*<<< orphan*/  proto; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int getservbyname_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct servent*,char*,size_t,struct servent**) ; 

__attribute__((used)) static int
wrap_getservbyname_r(struct key key, struct servent *serv, char *buffer,
    size_t bufsize, struct servent **res)
{
	return (getservbyname_r(key.name, key.proto, serv, buffer, bufsize,
	    res));
}