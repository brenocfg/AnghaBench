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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int TCP_FASTOPEN_KEY_LEN ; 
 int /*<<< orphan*/  arc4rand (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_fastopen_addkey_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tcp_fastopen_autokey_locked(void)
{
	uint8_t newkey[TCP_FASTOPEN_KEY_LEN];

	arc4rand(newkey, TCP_FASTOPEN_KEY_LEN, 0);
	tcp_fastopen_addkey_locked(newkey);
}