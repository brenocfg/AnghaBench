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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  h2o_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 

__attribute__((used)) static socklen_t get_sockname(h2o_conn_t *conn, struct sockaddr *sa)
{
    struct sockaddr_in *sin = (void *)sa;
    sin->sin_family = AF_INET;
    sin->sin_addr.s_addr = htonl(0x7f000001);
    sin->sin_port = htons(80);
    return sizeof(*sin);
}