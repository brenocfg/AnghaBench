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
typedef  enum gas_query_ap_result { ____Placeholder_gas_query_ap_result } gas_query_ap_result ;

/* Variables and functions */
#define  GAS_QUERY_AP_DELETED_AT_DEINIT 133 
#define  GAS_QUERY_AP_FAILURE 132 
#define  GAS_QUERY_AP_INTERNAL_ERROR 131 
#define  GAS_QUERY_AP_PEER_ERROR 130 
#define  GAS_QUERY_AP_SUCCESS 129 
#define  GAS_QUERY_AP_TIMEOUT 128 

__attribute__((used)) static const char * gas_result_txt(enum gas_query_ap_result result)
{
	switch (result) {
	case GAS_QUERY_AP_SUCCESS:
		return "SUCCESS";
	case GAS_QUERY_AP_FAILURE:
		return "FAILURE";
	case GAS_QUERY_AP_TIMEOUT:
		return "TIMEOUT";
	case GAS_QUERY_AP_PEER_ERROR:
		return "PEER_ERROR";
	case GAS_QUERY_AP_INTERNAL_ERROR:
		return "INTERNAL_ERROR";
	case GAS_QUERY_AP_DELETED_AT_DEINIT:
		return "DELETED_AT_DEINIT";
	}

	return "N/A";
}