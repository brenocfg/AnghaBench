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
#define  FAILURE 133 
#define  PWD_Commit_Req 132 
#define  PWD_Confirm_Req 131 
#define  PWD_ID_Req 130 
#define  SUCCESS 129 
#define  SUCCESS_ON_FRAG_COMPLETION 128 

__attribute__((used)) static const char * eap_pwd_state_txt(int state)
{
	switch (state) {
        case PWD_ID_Req:
		return "PWD-ID-Req";
        case PWD_Commit_Req:
		return "PWD-Commit-Req";
        case PWD_Confirm_Req:
		return "PWD-Confirm-Req";
	case SUCCESS_ON_FRAG_COMPLETION:
		return "SUCCESS_ON_FRAG_COMPLETION";
        case SUCCESS:
		return "SUCCESS";
        case FAILURE:
		return "FAILURE";
        default:
		return "PWD-UNK";
	}
}