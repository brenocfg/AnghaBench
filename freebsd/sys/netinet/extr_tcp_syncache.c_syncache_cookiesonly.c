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
struct TYPE_2__ {scalar_t__ paused; } ;

/* Variables and functions */
 TYPE_1__ V_tcp_syncache ; 
 scalar_t__ V_tcp_syncookies ; 
 scalar_t__ V_tcp_syncookiesonly ; 

__attribute__((used)) static inline bool
syncache_cookiesonly(void)
{

	return (V_tcp_syncookies && (V_tcp_syncache.paused ||
	    V_tcp_syncookiesonly));
}