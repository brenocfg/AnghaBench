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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ newest; int /*<<< orphan*/ * key; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_FASTOPEN_KEY_LEN ; 
 scalar_t__ TCP_FASTOPEN_MAX_KEYS ; 
 TYPE_1__ V_tcp_fastopen_keys ; 
 scalar_t__ V_tcp_fastopen_numkeys ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tcp_fastopen_addkey_locked(uint8_t *key)
{

	V_tcp_fastopen_keys.newest++;
	if (V_tcp_fastopen_keys.newest == TCP_FASTOPEN_MAX_KEYS)
		V_tcp_fastopen_keys.newest = 0;
	memcpy(V_tcp_fastopen_keys.key[V_tcp_fastopen_keys.newest], key,
	    TCP_FASTOPEN_KEY_LEN);
	if (V_tcp_fastopen_numkeys < TCP_FASTOPEN_MAX_KEYS)
		V_tcp_fastopen_numkeys++;
}