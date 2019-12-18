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
typedef  enum sec_status { ____Placeholder_sec_status } sec_status ;

/* Variables and functions */
#define  sec_status_bogus 133 
#define  sec_status_indeterminate 132 
#define  sec_status_insecure 131 
#define  sec_status_secure 130 
#define  sec_status_secure_sentinel_fail 129 
#define  sec_status_unchecked 128 

const char* 
sec_status_to_string(enum sec_status s)
{
	switch(s) {
	case sec_status_unchecked: 	return "sec_status_unchecked";
	case sec_status_bogus: 		return "sec_status_bogus";
	case sec_status_indeterminate: 	return "sec_status_indeterminate";
	case sec_status_insecure: 	return "sec_status_insecure";
	case sec_status_secure_sentinel_fail: 	return "sec_status_secure_sentinel_fail";
	case sec_status_secure: 	return "sec_status_secure";
	}
	return "unknown_sec_status_value";
}