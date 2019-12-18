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
#define  KEY_RX_KEY_RECEIVE 129 
#define  KEY_RX_NO_KEY_RECEIVE 128 

__attribute__((used)) static inline const char * key_rx_state_txt(int s)
{
	switch (s) {
	case KEY_RX_NO_KEY_RECEIVE: return "NO_KEY_RECEIVE";
	case KEY_RX_KEY_RECEIVE: return "KEY_RECEIVE";
	default: return "Unknown";
	}
}