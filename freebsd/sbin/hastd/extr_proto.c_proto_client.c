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
struct proto_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROTO_SIDE_CLIENT ; 
 int proto_common_setup (char const*,char const*,struct proto_conn**,int /*<<< orphan*/ ) ; 

int
proto_client(const char *srcaddr, const char *dstaddr,
    struct proto_conn **connp)
{

	return (proto_common_setup(srcaddr, dstaddr, connp, PROTO_SIDE_CLIENT));
}