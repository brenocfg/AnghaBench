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
#define  BE_AUTH_FAIL 135 
#define  BE_AUTH_IDLE 134 
#define  BE_AUTH_IGNORE 133 
#define  BE_AUTH_INITIALIZE 132 
#define  BE_AUTH_REQUEST 131 
#define  BE_AUTH_RESPONSE 130 
#define  BE_AUTH_SUCCESS 129 
#define  BE_AUTH_TIMEOUT 128 

__attribute__((used)) static inline const char * be_auth_state_txt(int s)
{
	switch (s) {
	case BE_AUTH_REQUEST: return "REQUEST";
	case BE_AUTH_RESPONSE: return "RESPONSE";
	case BE_AUTH_SUCCESS: return "SUCCESS";
	case BE_AUTH_FAIL: return "FAIL";
	case BE_AUTH_TIMEOUT: return "TIMEOUT";
	case BE_AUTH_IDLE: return "IDLE";
	case BE_AUTH_INITIALIZE: return "INITIALIZE";
	case BE_AUTH_IGNORE: return "IGNORE";
	default: return "Unknown";
	}
}