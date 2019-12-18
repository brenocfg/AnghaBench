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
struct key {char const* name; char const* proto; } ;

/* Variables and functions */
 struct servent* getserv (int /*<<< orphan*/ ,struct key) ; 
 int /*<<< orphan*/  wrap_getservbyname_r ; 

struct servent *
getservbyname(const char *name, const char *proto)
{
	struct key key;

	key.name = name;
	key.proto = proto;

	return (getserv(wrap_getservbyname_r, key));
}