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

/* Variables and functions */
#define  AUTH_KEY_TX_KEY_TRANSMIT 129 
#define  AUTH_KEY_TX_NO_KEY_TRANSMIT 128 

__attribute__((used)) static inline const char * auth_key_tx_state_txt(int s)
{
	switch (s) {
	case AUTH_KEY_TX_NO_KEY_TRANSMIT: return "NO_KEY_TRANSMIT";
	case AUTH_KEY_TX_KEY_TRANSMIT: return "KEY_TRANSMIT";
	default: return "Unknown";
	}
}