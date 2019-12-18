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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_ACTIVE ; 
 int /*<<< orphan*/  MODE_BROADCAST ; 
 int /*<<< orphan*/  MODE_CLIENT ; 
#define  T_Broadcast 132 
#define  T_Manycastclient 131 
#define  T_Peer 130 
#define  T_Pool 129 
#define  T_Server 128 

__attribute__((used)) static u_char
get_correct_host_mode(
	int token
	)
{
	switch (token) {

	case T_Server:
	case T_Pool:
	case T_Manycastclient:
		return MODE_CLIENT;

	case T_Peer:
		return MODE_ACTIVE;

	case T_Broadcast:
		return MODE_BROADCAST;

	default:
		return 0;
	}
}