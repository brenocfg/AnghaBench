#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_7__ {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct TYPE_8__ {TYPE_2__ sa4; } ;
typedef  TYPE_3__ sockaddr_u ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  SET_PORT (TYPE_3__*,int) ; 
 int /*<<< orphan*/  inet_addr (char const*) ; 

sockaddr_u
CreateSockaddr4(const char* address) {
	sockaddr_u s;
	s.sa4.sin_family = AF_INET;
	s.sa4.sin_addr.s_addr = inet_addr(address);
	SET_PORT(&s, 123);

	return s;
}