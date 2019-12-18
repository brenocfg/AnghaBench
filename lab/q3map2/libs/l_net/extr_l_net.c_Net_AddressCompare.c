#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ip; } ;
typedef  TYPE_1__ address_t ;

/* Variables and functions */
 int strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int Net_AddressCompare( address_t *addr1, address_t *addr2 ){
#ifdef _WIN32
	return stricmp( addr1->ip, addr2->ip );
#elif defined( __linux__ ) || defined( __FreeBSD__ ) || defined( __APPLE__ )
	return strcasecmp( addr1->ip, addr2->ip );
#else
	#error unknown architecture
#endif
}