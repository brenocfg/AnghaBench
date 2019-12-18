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
#define  AUTH_PAE_ABORTING 137 
#define  AUTH_PAE_AUTHENTICATED 136 
#define  AUTH_PAE_AUTHENTICATING 135 
#define  AUTH_PAE_CONNECTING 134 
#define  AUTH_PAE_DISCONNECTED 133 
#define  AUTH_PAE_FORCE_AUTH 132 
#define  AUTH_PAE_FORCE_UNAUTH 131 
#define  AUTH_PAE_HELD 130 
#define  AUTH_PAE_INITIALIZE 129 
#define  AUTH_PAE_RESTART 128 

__attribute__((used)) static inline const char * auth_pae_state_txt(int s)
{
	switch (s) {
	case AUTH_PAE_INITIALIZE: return "INITIALIZE";
	case AUTH_PAE_DISCONNECTED: return "DISCONNECTED";
	case AUTH_PAE_CONNECTING: return "CONNECTING";
	case AUTH_PAE_AUTHENTICATING: return "AUTHENTICATING";
	case AUTH_PAE_AUTHENTICATED: return "AUTHENTICATED";
	case AUTH_PAE_ABORTING: return "ABORTING";
	case AUTH_PAE_HELD: return "HELD";
	case AUTH_PAE_FORCE_AUTH: return "FORCE_AUTH";
	case AUTH_PAE_FORCE_UNAUTH: return "FORCE_UNAUTH";
	case AUTH_PAE_RESTART: return "RESTART";
	default: return "Unknown";
	}
}